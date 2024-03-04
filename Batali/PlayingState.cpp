#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, bool twoPlayers, const std::string& firstCharacter, const std::string& secondCharacter)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
	, m_twoPlayers{ twoPlayers }
{
	m_currentState = PLAYING_STATE;

	// Initialize Player 1
	if (firstCharacter == "fire_knight")
	{
		m_players.emplace_back(std::make_shared<FireKnight>(LEFT_CHARACTER_FIRST_POSITION));
		characterStatus1.init("fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() - m_view.getSize() / 2.f);
	}
	else
	{
		m_players.emplace_back(std::make_shared<WindHashashin>(LEFT_CHARACTER_FIRST_POSITION));
		characterStatus1.init("windHashashinLogo", "./assets/windHashashinLogo.png", m_view.getCenter() - m_view.getSize() / 2.f);
	}

	characterStatus1.m_healthBar.setEntityStatus(&m_players[0]->getHp());
	characterStatus1.m_staminaBar.setEntityStatus(&m_players[0]->getStamina());
	characterStatus1.m_manaBar.setEntityStatus(&m_players[0]->getRemainingManaToUltimate());

	// Initialize Player 2 or Enemy
	if (m_twoPlayers)
	{
		if (secondCharacter == "fire_knight")
		{
			m_players.emplace_back(std::make_shared<FireKnight>(RIGHT_CHARACTER_FIRST_POSITION, 2));
			characterStatus2.init("fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}
		else
		{
			m_players.emplace_back(std::make_shared<WindHashashin>(RIGHT_CHARACTER_FIRST_POSITION, 2));
			characterStatus2.init("windHashashinLogo", "./assets/windHashashinLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}

		characterStatus2.m_healthBar.setEntityStatus(&m_players[1]->getHp());
		characterStatus2.m_staminaBar.setEntityStatus(&m_players[1]->getStamina());
		characterStatus2.m_manaBar.setEntityStatus(&m_players[1]->getRemainingManaToUltimate());
	}
	else
	{
		if (secondCharacter == "fire_knight")
		{
			m_bots.emplace_back(std::make_unique<FireKnight>(RIGHT_CHARACTER_FIRST_POSITION, 0, true, m_players[0]));
			characterStatus2.init("fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}
		else
		{
			m_bots.emplace_back(std::make_unique<WindHashashin>(RIGHT_CHARACTER_FIRST_POSITION, 0, true, m_players[0]));
			characterStatus2.init("windHashashinLogo", "./assets/windHashashinLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}

		characterStatus2.m_healthBar.setEntityStatus(&m_bots[0]->getHp());
		characterStatus2.m_staminaBar.setEntityStatus(&m_bots[0]->getStamina());
		characterStatus2.m_manaBar.setEntityStatus(&m_bots[0]->getRemainingManaToUltimate());
	}

	// Initialize map
	loadAndCreateMap("./map/map.txt");

	// Initialize Threads
	animationThread = std::thread(&PlayingState::updateTexturesAndAnimations, this);
	playerInputThread = std::thread(&PlayingState::updatePlayerInput, this);

	// Initialize View
	m_view = m_window.getDefaultView();
	m_view.zoom(0.5f);
	m_window.setView(m_view);
}

PlayingState::~PlayingState()
{
	animationThread.join();
	playerInputThread.join();
}

void PlayingState::update()
{
	if (m_pressedKey == sf::Keyboard::Scancode::P)
	{
		m_onPause = !m_onPause;
	}

	if (m_pressedKey == sf::Keyboard::Scancode::T)
	{
		m_debugMode = !m_debugMode;
	}
	
	if (!m_onPause)
	{
		updateCollision();

		characterStatus1.update();
		characterStatus2.update();

		for (auto& player : m_players)
		{
			player->update(m_deltaTime);
		}

		for (auto& bot : m_bots)
		{
			bot->update(m_deltaTime);
		}

		updateView();
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void PlayingState::render()
{
	for (auto& player : m_players)
	{
		if (m_debugMode)
			m_window.draw(player->getShape());
		m_window.draw(player->getSprite());
	}

	for (auto& bot : m_bots)
	{
		if (m_debugMode)
			m_window.draw(bot->getShape());
		m_window.draw(bot->getSprite());
		if (m_debugMode)
			m_window.draw(bot->getAttackHitbox());
	}

	if (m_debugMode)
		for (auto& player : m_players)
		{
			m_window.draw(player->getAttackHitbox());
			m_window.draw(player->getUltimateActivateHitbox());
		}

	for (auto& ground : m_grounds)
	{
		// Only draw the tiles that are inside the view
		if (ground.getSprite().getPosition().x <= m_rightViewLimit && ground.getSprite().getPosition().x >= m_leftViewLimit
			&& ground.getSprite().getPosition().y >= m_topViewLimit && ground.getSprite().getPosition().y <= m_bottomViewLimit)
		{
			m_window.draw(ground.getSprite());
		}
	}

	m_window.draw(characterStatus1.getSprite());
	m_window.draw(characterStatus1.m_healthBar.getSprite());
	m_window.draw(characterStatus1.m_staminaBar.getSprite());
	m_window.draw(characterStatus1.m_manaBar.getSprite());

	m_window.draw(characterStatus2.getSprite());
	m_window.draw(characterStatus2.m_healthBar.getSprite());
	m_window.draw(characterStatus2.m_staminaBar.getSprite());
	m_window.draw(characterStatus2.m_manaBar.getSprite());
}

void PlayingState::updateCollision()
{
	// We reset isCollidingHorizontally to false for all entities, so when isColliding() is called, if the entity collides in the x-direction, it will be true.
	// If doesn't collide, it remains false.

	for (auto& player : m_players)
	{
		player->setIsCollidingHorizontally(false);
	}
	
	for (auto& bot : m_bots)
	{
		bot->setIsCollidingHorizontally(false);
	}

	// Entities' collision with tiles
	for (auto& ground : m_grounds)
	{
		// Player's collision
		for (auto& player : m_players)
		{
			updateEntityCollisionWithGrounds(*player, ground);
		}

		// Bots' collision
		for (auto& bot : m_bots)
		{
			updateEntityCollisionWithGrounds(*bot, ground);
		}
	}

	if (m_twoPlayers)
	{
		if (m_players[1]->getShape().getGlobalBounds().intersects((m_players[0]->getAttackHitbox().getGlobalBounds())) && !m_players[1]->isDying())
		{
			handleEntityAttacked(*(m_players[0]), *(m_players[1]));
		}

		if (m_players[0]->getShape().getGlobalBounds().intersects((m_players[1]->getAttackHitbox().getGlobalBounds())) && !m_players[0]->isDying())
		{
			handleEntityAttacked(*(m_players[1]), *(m_players[0]));
		}

		if (m_players[1]->getShape().getGlobalBounds().intersects((m_players[0]->getUltimateActivateHitbox().getGlobalBounds())) && !m_players[1]->isDying())
		{
			handleEntityAttacked(*(m_players[0]), *(m_players[1]), true);
		}

		if (m_players[0]->getShape().getGlobalBounds().intersects((m_players[1]->getUltimateActivateHitbox().getGlobalBounds())) && !m_players[0]->isDying())
		{
			handleEntityAttacked(*(m_players[1]), *(m_players[0]), true);
		}
	}

	// Checks if the an entity was attacked by another entity
	for (auto& bot : m_bots)
	{
		// Bot attacked by player
		if (bot->getShape().getGlobalBounds().intersects((m_players[0]->getAttackHitbox().getGlobalBounds())) && !bot->isDying())
		{
			handleEntityAttacked(*(m_players[0]), *(bot));
		}

		// Player attacked by an bot
		if (m_players[0]->getShape().getGlobalBounds().intersects((bot->getAttackHitbox().getGlobalBounds())) && !m_players[0]->isDying())
		{
			handleEntityAttacked(*(bot), *(m_players[0]));
		}
	}
}

void PlayingState::updateEntityCollisionWithGrounds(MovableEntity& entity, Ground& ground)
{
	if (ground.getSprite().getPosition().x <= entity.m_rightLimit && ground.getSprite().getPosition().x >= entity.m_leftLimit
		&& ground.getSprite().getPosition().y >= entity.m_topLimit && ground.getSprite().getPosition().y <= entity.m_bottomLimit)
	{
		if (entity.isCollidingWith(ground.getSprite()))
		{
			entity.handleCollision();
		}
	}
}

void PlayingState::handleEntityAttacked(SwordEntity& attackingEntity, DamageEntity& attackedEntity, bool isUltimateActivate)
{
	// If attackDirection is negative, the attack came from the right. Otherwise, it came from left.
	float attackDirection = attackingEntity.getShapePosition().x - attackedEntity.getShapePosition().x;

	if (attackingEntity.getDamage() == WIND_HASHASHIN_ULTIMATE_DAMAGE)
	{
		attackedEntity.setOnWindHashashinUltimate(true);
	}
	else
	{
		attackedEntity.setOnWindHashashinUltimate(false);
	}

	if (!isUltimateActivate)
	{
		bool gotHit = attackedEntity.takeDamage(m_deltaTime, attackDirection, attackingEntity.getDamage());

		if (gotHit && attackingEntity.getDamage() != WIND_HASHASHIN_ULTIMATE_DAMAGE)
		{
			// Knockback of the attackedEntity. The attackedEntity will be pushed until it doesn't collide with the hitbox anymore or until it collides with a wall. It's not pushed if attacked entity is on roll. 
			while (attackedEntity.getShape().getGlobalBounds().intersects((attackingEntity.getAttackHitbox().getGlobalBounds())) && !attackedEntity.getIsCollidingHorizontally() && !attackedEntity.getOnRoll())
			{
				for (auto& ground : m_grounds)
				{
					updateEntityCollisionWithGrounds(attackedEntity, ground);
				}
				attackedEntity.knockbackMove(m_deltaTime, attackDirection);
			}
		}
	}
	else
	{
		attackedEntity.setShapePosition(attackingEntity.getShapePosition());
		attackedEntity.setSpritePosition(sf::Vector2f{ attackedEntity.getShapePosition().x, attackedEntity.getShapePosition().y - (attackedEntity.getSpriteSize().y - attackedEntity.getShapeSize().y) / 2.f });
		
		attackingEntity.setActivateUltimate(true);
	}
}

void PlayingState::updateView()
{
	m_view.setCenter((TILES_AMOUNT_PER_ROW / 2.f) * TILE_SIZE_FLOAT, (TILES_AMOUNT_PER_COL / 2.f) * TILE_SIZE_FLOAT);
	m_window.setView(m_view);

	characterStatus2.setSpritePosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f });

	characterStatus2.m_healthBar.setSpritePosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f } - sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, 0.f });
	characterStatus2.m_staminaBar.setSpritePosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f } - sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, -1.f * HEALTH_BAR_HEIGHT });
	characterStatus2.m_manaBar.setSpritePosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f } - sf::Vector2f{ CHARACTER_LOGO_STATUS_WIDTH, -1.f * (HEALTH_BAR_HEIGHT + STAMINA_BAR_HEIGHT)});

	m_rightViewLimit = m_view.getCenter().x + m_view.getSize().x / 2.f + TILE_SIZE_FLOAT;
	m_leftViewLimit = m_view.getCenter().x - m_view.getSize().x / 2.f - TILE_SIZE_FLOAT;

	m_topViewLimit = m_view.getCenter().y - m_view.getSize().y / 2.f - TILE_SIZE_FLOAT;
	m_bottomViewLimit = m_view.getCenter().y + m_view.getSize().y / 2.f + TILE_SIZE_FLOAT;
}

void PlayingState::loadAndCreateMap(const std::string& mapFilePath)
{
	std::fstream mapFile{ mapFilePath, std::ios::in };
	std::string row{};

	int x{ 0 };
	int y{ 0 };

	std::string tileId{};

	while (std::getline(mapFile, row))
	{
		for (int i = 0; i < TILES_AMOUNT_PER_ROW; i++)
		{
			mapFile >> tileId;
			if (tileId != "0")
			{
				m_grounds.emplace_back(Ground{ sf::Vector2f{x * TILE_SIZE_FLOAT + TILE_SIZE_FLOAT / 2.f, y * TILE_SIZE_FLOAT + TILE_SIZE_FLOAT / 2.f}, tileId,  "./tiles/" + tileId + ".png"});
			}
			++x;
		}
		x = 0;
		++y;
	}

	mapFile.close();
}

void PlayingState::updateTexturesAndAnimations()
{
	while (m_currentState == PLAYING_STATE)
	{
		if (!m_onPause)
		{
			// If there isn't a thread sleep or if the milliseconds time is too short, the animation will run so fast that it bugs and doesn't display sprites correctly
			std::this_thread::sleep_for(std::chrono::milliseconds(75));

			for (auto& player : m_players)
			{
				if (!player->isDead())
				{
					player->updateAnimation();
				}
			}

			for (auto& bot : m_bots)
			{
				if (!bot->isDead())
				{
					bot->updateAnimation();
				}
			}
		}
	}
}

void PlayingState::updatePlayerInput()
{
	while (m_currentState == PLAYING_STATE)
	{
		if (!m_onPause)
		{
			for (auto& player : m_players)
			{
				if (player->getPlayerNumber() == 1)
				{
					if (m_twoPlayers)
					{
						player->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A));
						player->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D));
						player->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W));

						player->setConditionAttack1(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X));
						player->setConditionAttack2(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C));

						player->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V));

						player->setConditionUltimate(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B));
					}
					else
					{
						player->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left));
						player->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right));
						player->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up));

						player->setConditionAttack1(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z));
						player->setConditionAttack2(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X));
						
						player->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C));

						player->setConditionUltimate(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V));
					}
				}
				else if (player->getPlayerNumber() == 2)
				{
					player->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left));
					player->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right));
					player->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up));

					player->setConditionAttack1(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I));
					player->setConditionAttack2(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O));

					player->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::J));

					player->setConditionUltimate(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K));
				}
			}
		}
	}
}
