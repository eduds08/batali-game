#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, bool twoPlayers, const std::string& firstCharacter, const std::string& secondCharacter)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
	, m_twoPlayers{ twoPlayers }
{
	m_currentState = constants::playingState;

	// Initialize Player 1
	if (firstCharacter == "fire_knight")
	{
		m_players.emplace_back(std::make_shared<FireKnight>(leftCharacterFirstPosition));
		characterStatus1.init("fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() - m_view.getSize() / 2.f);
	}
	else
	{
		m_players.emplace_back(std::make_shared<WindHashashin>(leftCharacterFirstPosition));
		characterStatus1.init("windHashashinLogo", "./assets/windHashashinLogo.png", m_view.getCenter() - m_view.getSize() / 2.f);
	}

	characterStatus1.m_healthBar.setEntityStatus(&m_players[0]->getHp());
	characterStatus1.m_staminaBar.setEntityStatus(&m_players[0]->m_stamina);
	characterStatus1.m_manaBar.setEntityStatus(&m_players[0]->m_remainingManaToUltimate);

	// Initialize Player 2 or Enemy
	if (m_twoPlayers)
	{
		if (secondCharacter == "fire_knight")
		{
			m_players.emplace_back(std::make_shared<FireKnight>(rightCharacterFirstPosition, 2));
			characterStatus2.init("fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}
		else
		{
			m_players.emplace_back(std::make_shared<WindHashashin>(rightCharacterFirstPosition, 2));
			characterStatus2.init("windHashashinLogo", "./assets/windHashashinLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}

		characterStatus2.m_healthBar.setEntityStatus(&m_players[1]->getHp());
		characterStatus2.m_staminaBar.setEntityStatus(&m_players[1]->m_stamina);
		characterStatus2.m_manaBar.setEntityStatus(&m_players[1]->m_remainingManaToUltimate);
	}
	else
	{
		if (secondCharacter == "fire_knight")
		{
			m_bots.emplace_back(std::make_unique<FireKnight>(rightCharacterFirstPosition, 0, true, m_players[0]));
			characterStatus2.init("fireKnightLogo", "./assets/fireKnightLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}
		else
		{
			m_bots.emplace_back(std::make_unique<WindHashashin>(rightCharacterFirstPosition, 0, true, m_players[0]));
			characterStatus2.init("windHashashinLogo", "./assets/windHashashinLogo.png", m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f }, false);
		}

		characterStatus2.m_healthBar.setEntityStatus(&m_bots[0]->getHp());
		characterStatus2.m_staminaBar.setEntityStatus(&m_bots[0]->m_stamina);
		characterStatus2.m_manaBar.setEntityStatus(&m_bots[0]->m_remainingManaToUltimate);
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
	m_pauseDelay = m_pauseClock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P) && m_pauseDelay > 0.3f)
	{
		m_onPause = !m_onPause;
		m_pauseClock.restart();
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
}

void PlayingState::render()
{
	for (auto& player : m_players)
	{
		m_window.draw(player->getShape());
		m_window.draw(player->getSprite());
	}

	for (auto& bot : m_bots)
	{
		m_window.draw(bot->getShape());
		m_window.draw(bot->getSprite());
		m_window.draw(bot->getAttackHitbox());
	}

	for (auto& player : m_players)
	{
		m_window.draw(player->getAttackHitbox());
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

void PlayingState::handleEntityAttacked(SwordEntity& attackingEntity, DamageEntity& attackedEntity)
{
	// If attackDirection is negative, the attack came from the right. Otherwise, it came from left.
	float attackDirection = attackingEntity.getShapePosition().x - attackedEntity.getShapePosition().x;

	attackedEntity.takeDamage(m_deltaTime, attackDirection, attackingEntity.getDamage());

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

void PlayingState::updateView()
{
	m_view.setCenter((tilesAmountPerRow / 2.f) * tileSizeF, (tilesAmountPerCol / 2.f) * tileSizeF);
	m_window.setView(m_view);

	characterStatus2.setPosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f });

	characterStatus2.m_healthBar.setPosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f } - sf::Vector2f{ 78.f * 3.f / 4.f, 0.f });
	characterStatus2.m_staminaBar.setPosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f } - sf::Vector2f{ 78.f * 3.f / 4.f, -18.f * 3.f / 4.f });
	characterStatus2.m_manaBar.setPosition(m_view.getCenter() + sf::Vector2f{ (m_view.getSize().x / 2.f), -m_view.getSize().y / 2.f } - sf::Vector2f{ 78.f * 3.f / 4.f, -36.f * 3.f / 4.f });

	m_rightViewLimit = m_view.getCenter().x + m_view.getSize().x / 2.f + tileSizeF;
	m_leftViewLimit = m_view.getCenter().x - m_view.getSize().x / 2.f - tileSizeF;

	m_topViewLimit = m_view.getCenter().y - m_view.getSize().y / 2.f - tileSizeF;
	m_bottomViewLimit = m_view.getCenter().y + m_view.getSize().y / 2.f + tileSizeF;
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
		for (int i = 0; i < tilesAmountPerRow; i++)
		{
			mapFile >> tileId;
			if (tileId != "0")
			{
				m_grounds.emplace_back(Ground{ sf::Vector2f{x * tileSizeF + tileSizeF / 2.f, y * tileSizeF + tileSizeF / 2.f}, tileId,  "./tiles/" + tileId + ".png"});
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
	while (m_currentState == constants::playingState)
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
	while (m_currentState == constants::playingState)
	{
		if (!m_onPause)
		{
			for (auto& player : m_players)
			{
				if (player->getPlayerNumber() == 1)
				{
					player->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left));
					player->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right));
					player->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up));

					player->setConditionAttack(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::L));

					player->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K));
				}
				else if (player->getPlayerNumber() == 2)
				{
					player->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A));
					player->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D));
					player->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W));

					player->setConditionAttack(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift));

					player->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space));
				}
			}
		}
	}
}
