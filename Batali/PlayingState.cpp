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
		m_characters.emplace_back(std::make_shared<Player<FireKnight>>(LEFT_CHARACTER_FIRST_POSITION));
	}
	else if (firstCharacter == "wind_hashashin")
	{
		m_characters.emplace_back(std::make_shared<Player<WindHashashin>>(LEFT_CHARACTER_FIRST_POSITION));
	}
	else if (firstCharacter == "boxer")
	{
		m_characters.emplace_back(std::make_shared<Player<Boxer>>(LEFT_CHARACTER_FIRST_POSITION));
	}

	m_characterStatus.emplace_back(CharacterStatusUI{ firstCharacter + "Logo", "./assets/" + firstCharacter + "/logo.png", m_characters[0].get() });

	// Initialize Player 2 or Enemy
	if (m_twoPlayers)
	{
		if (secondCharacter == "fire_knight")
		{
			m_characters.emplace_back(std::make_shared<Player<FireKnight>>(RIGHT_CHARACTER_FIRST_POSITION, 2));
		}
		else if (secondCharacter == "wind_hashashin")
		{
			m_characters.emplace_back(std::make_shared<Player<WindHashashin>>(RIGHT_CHARACTER_FIRST_POSITION, 2));
		}
		else if (secondCharacter == "boxer")
		{
			m_characters.emplace_back(std::make_shared<Player<Boxer>>(RIGHT_CHARACTER_FIRST_POSITION, 2));
		}

		m_player2InputThread = std::thread(&PlayingState::updatePlayer2Input, this);
	}
	else
	{
		if (secondCharacter == "fire_knight")
		{
			m_characters.emplace_back(std::make_unique<EnemyBot<FireKnight>>(RIGHT_CHARACTER_FIRST_POSITION, m_characters[0]->getShapePosition(), m_characters[0]->getShapeSize()));
		}
		else if (secondCharacter == "wind_hashashin")
		{
			m_characters.emplace_back(std::make_unique<EnemyBot<WindHashashin>>(RIGHT_CHARACTER_FIRST_POSITION, m_characters[0]->getShapePosition(), m_characters[0]->getShapeSize()));
		}
		else if (secondCharacter == "boxer")
		{
			m_characters.emplace_back(std::make_shared<EnemyBot<Boxer>>(RIGHT_CHARACTER_FIRST_POSITION, m_characters[0]->getShapePosition(), m_characters[0]->getShapeSize()));
		}
	}

	m_characterStatus.emplace_back(CharacterStatusUI{ secondCharacter + "Logo", "./assets/" + secondCharacter + "/logo.png", m_characters[1].get(), true });

	// Initialize map
	loadAndCreateMap("./map/map.txt");

	// Initialize Threads
	m_animationThread = std::thread(&PlayingState::updateTexturesAndAnimations, this);
	m_player1InputThread = std::thread(&PlayingState::updatePlayer1Input, this);
}

PlayingState::~PlayingState()
{
	m_animationThread.join();
	m_player1InputThread.join();

	if (m_twoPlayers)
	{
		m_player2InputThread.join();
	}
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

			if (dynamic_cast<WindHashashin*>(character.get()) != nullptr)
			{
				m_window.draw(dynamic_cast<WindHashashin*>(character.get())->getUltimateActivateHitbox());
			}
		}
		m_window.draw(character->getSprite());

		if (dynamic_cast<Boxer*>(character.get()) != nullptr)
		{
			for (auto& projectile : dynamic_cast<Boxer*>(character.get())->getProjectiles())
			{
				if (m_debugMode)
				{
					m_window.draw(projectile->getShape());
				}
				m_window.draw(projectile->getSprite());
			}
		}
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
		m_characters[0]->setOnFreeze(false);
		m_characters[1]->setOnFreeze(false);
	}

	for (auto& attackedCharacter : m_characters)
	{
		for (auto& attackingCharacter : m_characters)
		{
			if (attackedCharacter != attackingCharacter)
			{
				bool isUltimateActivate = false;

				if (attackedCharacter->isCollidingWithAttack(*attackingCharacter, isUltimateActivate))
				{
					handleEntityAttacked(*attackingCharacter, *attackedCharacter, isUltimateActivate);
				}
			}
		}
	}
}

void PlayingState::updateEntityCollisionWithGrounds(WalkingEntity& entity, Ground& ground)
{
	if (ground.getSprite().getPosition().x <= entity.getShapeLimits()[1] && ground.getSprite().getPosition().x >= entity.getShapeLimits()[3]
		&& ground.getSprite().getPosition().y >= entity.getShapeLimits()[0] && ground.getSprite().getPosition().y <= entity.getShapeLimits()[2])
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
				if (!character->getDead())
				{
					character->updateAnimation();

					if (dynamic_cast<Boxer*>(character.get()) != nullptr)
					{
						for (auto& projectile : dynamic_cast<Boxer*>(character.get())->getProjectiles())
						{
							projectile->updateAnimation();
						}
					}
				}
			}
		}
	}
}

void PlayingState::updatePlayer1Input()
{
	while (m_currentState == PLAYING_STATE)
	{
		if (!m_onPause)
		{
			if (dynamic_cast<FireKnight*>(m_characters[0].get()) != nullptr)
			{
				setPlayerInput<FireKnight>(dynamic_cast<Player<FireKnight>*>(m_characters[0].get()));
			}
			else if (dynamic_cast<WindHashashin*>(m_characters[0].get()) != nullptr)
			{
				setPlayerInput<WindHashashin>(dynamic_cast<Player<WindHashashin>*>(m_characters[0].get()));
			}
			else if (dynamic_cast<Boxer*>(m_characters[0].get()) != nullptr)
			{
				setPlayerInput<Boxer>(dynamic_cast<Player<Boxer>*>(m_characters[0].get()));
			}
		}
	}
}

void PlayingState::updatePlayer2Input()
{
	while (m_currentState == PLAYING_STATE)
	{
		if (!m_onPause)
		{
			if (dynamic_cast<FireKnight*>(m_characters[1].get()) != nullptr)
			{
				setPlayerInput<FireKnight>(dynamic_cast<Player<FireKnight>*>(m_characters[1].get()));
			}
			else if (dynamic_cast<WindHashashin*>(m_characters[1].get()) != nullptr)
			{
				setPlayerInput<WindHashashin>(dynamic_cast<Player<WindHashashin>*>(m_characters[1].get()));
			}
			else if (dynamic_cast<Boxer*>(m_characters[1].get()) != nullptr)
			{
				setPlayerInput<Boxer>(dynamic_cast<Player<Boxer>*>(m_characters[1].get()));
			}
		}
	}
}
