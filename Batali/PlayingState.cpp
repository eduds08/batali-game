#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, bool twoPlayers, const std::string& firstCharacter, const std::string& secondCharacter)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
	, m_twoPlayers{ twoPlayers }
{
	m_currentState = PLAYING_STATE;

	// Initialize View
	m_view = m_window.getDefaultView();
	m_view.zoom(0.4f);

	// Initialize Player 1
	if (firstCharacter == "fire_knight")
	{
		m_characters.emplace_back(std::make_shared<FireKnight>(LEFT_CHARACTER_FIRST_POSITION));
		m_characterStatus.emplace_back(CharacterStatusUI{ "fireKnightLogo", "./assets/fireKnightLogo.png", m_characters[0].get() });
	}
	else
	{
		m_characters.emplace_back(std::make_shared<WindHashashin>(LEFT_CHARACTER_FIRST_POSITION));
		m_characterStatus.emplace_back(CharacterStatusUI{ "windHashashinLogo", "./assets/windHashashinLogo.png", m_characters[0].get() });
	}

	// Initialize Player 2 or Enemy
	if (m_twoPlayers)
	{
		if (secondCharacter == "fire_knight")
		{
			m_characters.emplace_back(std::make_shared<FireKnight>(RIGHT_CHARACTER_FIRST_POSITION, 2));
			m_characterStatus.emplace_back(CharacterStatusUI{ "fireKnightLogo", "./assets/fireKnightLogo.png", m_characters[1].get(), true });
		}
		else
		{
			m_characters.emplace_back(std::make_shared<WindHashashin>(RIGHT_CHARACTER_FIRST_POSITION, 2));
			m_characterStatus.emplace_back(CharacterStatusUI{ "windHashashinLogo", "./assets/windHashashinLogo.png", m_characters[1].get(), true });
		}
	}
	else
	{
		if (secondCharacter == "fire_knight")
		{
			m_characters.emplace_back(std::make_unique<FireKnight>(RIGHT_CHARACTER_FIRST_POSITION, 0, true, m_characters[0]));
			m_characterStatus.emplace_back(CharacterStatusUI{ "fireKnightLogo", "./assets/fireKnightLogo.png", m_characters[1].get(), true });
		}
		else
		{
			m_characters.emplace_back(std::make_unique<WindHashashin>(RIGHT_CHARACTER_FIRST_POSITION, 0, true, m_characters[0]));
			m_characterStatus.emplace_back(CharacterStatusUI{ "windHashashinLogo", "./assets/windHashashinLogo.png", m_characters[1].get(), true });
		}
	}

	// Initialize map
	loadAndCreateMap("./map/map.txt");

	// Initialize Threads
	animationThread = std::thread(&PlayingState::updateTexturesAndAnimations, this);
	playerInputThread = std::thread(&PlayingState::updatePlayerInput, this);
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

		for (auto& characterStatus : m_characterStatus)
		{
			characterStatus.update();
		}

		for (auto& character : m_characters)
		{
			character->update(m_deltaTime);
		}

		updateView();
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void PlayingState::render()
{
	for (auto& character : m_characters)
	{
		if (m_debugMode)
		{
			m_window.draw(character->getShape());
			m_window.draw(character->getAttackHitbox());
			m_window.draw(character->getUltimateActivateHitbox());
		}
		m_window.draw(character->getSprite());
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

	for (auto& characterStatus : m_characterStatus)
	{
		characterStatus.render(m_window);
	}
}

void PlayingState::updateCollision()
{
	// We reset isCollidingHorizontally to false for all entities, so when isColliding() is called, if the entity collides in the x-direction, it will be true.
	// If doesn't collide, it remains false.

	for (auto& character : m_characters)
	{
		character->setIsCollidingHorizontally(false);
	}

	// Entities' collision with tiles
	for (auto& ground : m_grounds)
	{
		// Player's collision
		for (auto& character : m_characters)
		{
			updateEntityCollisionWithGrounds(*character, ground);
		}
	}

	if (m_characters[0]->getDamage() != WIND_HASHASHIN_ULTIMATE_DAMAGE && m_characters[1]->getDamage() != WIND_HASHASHIN_ULTIMATE_DAMAGE)
	{
		m_characters[0]->setOnWindHashashinUltimate(false);
		m_characters[1]->setOnWindHashashinUltimate(false);
	}

	for (auto& attackedCharacter : m_characters)
	{
		for (auto& attackingCharacter : m_characters)
		{
			if (attackedCharacter != attackingCharacter)
			{
				if (attackedCharacter->getShape().getGlobalBounds().intersects(attackingCharacter->getAttackHitbox().getGlobalBounds()) && !attackedCharacter->isDying())
				{
					handleEntityAttacked(*attackingCharacter, *attackedCharacter);
				}
				if (attackedCharacter->getShape().getGlobalBounds().intersects(attackingCharacter->getUltimateActivateHitbox().getGlobalBounds()) && !attackedCharacter->isDying())
				{
					handleEntityAttacked(*attackingCharacter, *attackedCharacter, true);
				}
			}
		}
	}
}

void PlayingState::updateEntityCollisionWithGrounds(MovableEntity& entity, Ground& ground)
{
	if (ground.getSprite().getPosition().x <= entity.m_rightShapeLimit && ground.getSprite().getPosition().x >= entity.m_leftShapeLimit
		&& ground.getSprite().getPosition().y >= entity.m_topShapeLimit && ground.getSprite().getPosition().y <= entity.m_bottomShapeLimit)
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

		attackedEntity.setVelocity(sf::Vector2f{ 0.f, 0.f });

		attackingEntity.setActivateUltimate(true);
	}
}

void PlayingState::updateView()
{
	//m_view.setCenter((TILES_AMOUNT_PER_ROW / 2.f) * TILE_SIZE_FLOAT, (TILES_AMOUNT_PER_COL / 2.f) * TILE_SIZE_FLOAT);
	m_view.setCenter(m_characters[0]->getShapePosition());
	m_window.setView(m_view);

	m_characterStatus[0].updatePosition(m_view.getCenter(), m_view.getSize());
	m_characterStatus[1].updatePosition(m_view.getCenter(), m_view.getSize(), true);

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

			for (auto& character : m_characters)
			{
				if (!character->isDead())
				{
					character->updateAnimation();
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
			for (auto& character : m_characters)
			{
				if (character->getPlayerNumber() == 1)
				{
					if (m_twoPlayers)
					{
						character->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A));
						character->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D));
						character->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W));

						character->setConditionAttack1(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X));
						character->setConditionAttack2(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C));

						character->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V));

						character->setConditionUltimate(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B));
					}
					else
					{
						character->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left));
						character->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right));
						character->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up));

						character->setConditionAttack1(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z));
						character->setConditionAttack2(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X));

						character->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C));

						character->setConditionUltimate(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V));
					}
				}
				else if (character->getPlayerNumber() == 2)
				{
					character->setConditionRunLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left));
					character->setConditionRunRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right));
					character->setConditionJump(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up));

					character->setConditionAttack1(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I));
					character->setConditionAttack2(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O));

					character->setConditionRoll(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::J));

					character->setConditionUltimate(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K));
				}
			}
		}
	}
}
