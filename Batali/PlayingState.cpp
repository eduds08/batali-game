#include "PlayingState.h"

#include "HittedState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, const std::string& firstCharacter, const std::string& secondCharacter)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
{
	m_currentState = PLAYING_STATE;

	// Initialize View
	m_view = m_window.getDefaultView();
	m_view.zoom(0.4f);

	// Initialize Player 1
	if (firstCharacter == "fire_knight")
	{
		m_characters.emplace_back(std::make_shared<FireKnight>(LEFT_CHARACTER_FIRST_POSITION));
	}
	else if (firstCharacter == "wind_hashashin")
	{
		m_characters.emplace_back(std::make_shared<WindHashashin>(LEFT_CHARACTER_FIRST_POSITION));
	}
	else if (firstCharacter == "boxer")
	{
		m_characters.emplace_back(std::make_shared<Boxer>(LEFT_CHARACTER_FIRST_POSITION));
	}

	m_characterStatus.emplace_back(CharacterStatusUI{ firstCharacter + "Logo", "./assets/" + firstCharacter + "/logo.png", m_characters[0].get() });

	if (secondCharacter == "fire_knight")
	{
		m_characters.emplace_back(std::make_shared<FireKnight>(RIGHT_CHARACTER_FIRST_POSITION, 2));
	}
	else if (secondCharacter == "wind_hashashin")
	{
		m_characters.emplace_back(std::make_shared<WindHashashin>(RIGHT_CHARACTER_FIRST_POSITION, 2));
	}
	else if (secondCharacter == "boxer")
	{
		m_characters.emplace_back(std::make_shared<Boxer>(RIGHT_CHARACTER_FIRST_POSITION, 2));
	}

	m_characterStatus.emplace_back(CharacterStatusUI{ secondCharacter + "Logo", "./assets/" + secondCharacter + "/logo.png", m_characters[1].get(), true });

	// Initialize map
	loadAndCreateMap("./map/map.txt");

	// Initialize Threads
	m_animationThread = std::thread(&PlayingState::updateTexturesAndAnimations, this);
}

PlayingState::~PlayingState()
{
	m_animationThread.join();
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
			setPlayerInput(character.get());
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
		}

		character->render(m_window);

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

	for (auto& attackingCharacter : m_characters)
	{
		for (auto& attackedCharacter : m_characters)
		{
			if (attackedCharacter != attackingCharacter)
			{
				if (attackingCharacter->getStateName() == "AttackingState")
				{
					if (attackingCharacter->getCharacterState<AttackingState>()->checkAttack(*attackingCharacter, *attackedCharacter))
					{
						handleKnockbackMove(*attackingCharacter, *attackedCharacter, attackingCharacter->getCharacterState<AttackingState>()->m_attackHitbox->getIsUltimateActivate());
					}
				}
			}
		}
	}

	for (auto& attackingCharacter : m_characters)
	{
		for (auto& attackedCharacter : m_characters)
		{
			if (attackedCharacter != attackingCharacter)
			{
				// Was attacked by projectiles
				if (dynamic_cast<ProjectileEntity*>(attackingCharacter.get()) != nullptr)
				{
					for (auto& ultimateProjectile : dynamic_cast<ProjectileEntity*>(attackingCharacter.get())->getProjectiles())
					{
						if (ultimateProjectile->getShape().getGlobalBounds().intersects(attackedCharacter->getShape().getGlobalBounds()))
						{
							ultimateProjectile->setCollided(true);

							attackedCharacter->setState(new HittedState{ "FAST_HITTED", attackingCharacter.get() });
						}
					}
				}
			}
		}
	}
}

void PlayingState::updateEntityCollisionWithGrounds(ColliderEntity& entity, Ground& ground)
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

void PlayingState::handleKnockbackMove(Character& attackingEntity, Character& attackedEntity, bool isUltimateActivate)
{
	float attackDirection = attackingEntity.getShapePosition().x - attackedEntity.getShapePosition().x;

	if (!isUltimateActivate)
	{
		if (attackingEntity.getCharacterState<AttackingState>()->m_attackHitbox->getDamage() != WIND_HASHASHIN_ULTIMATE_DAMAGE)
		{
			// Knockback of the attackedEntity. The attackedEntity will be pushed until it doesn't collide with the hitbox anymore or until it collides with a wall. It's not pushed if attacked entity is on roll. 
			while (attackedEntity.getShape().getGlobalBounds().intersects((attackingEntity.getCharacterState<AttackingState>()->m_attackHitbox->getShape().getGlobalBounds())) && !attackedEntity.getIsCollidingHorizontally())
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

void PlayingState::setPlayerInput(Character* character)
{
	if (character->getPlayerNumber() == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
		{
			character->handleCondition("RUN");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
		{
			character->handleCondition("RUN");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
		{
			character->handleCondition("JUMP");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V))
		{
			character->handleCondition("ROLL");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X))
		{
			character->handleCondition("ATTACK_1");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C))
		{
			character->handleCondition("ATTACK_2");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B))
		{
			character->handleCondition("ULTIMATE");
		}
	}
	else if (character->getPlayerNumber() == 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
		{
			character->handleCondition("RUN");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
		{
			character->handleCondition("RUN");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
		{
			character->handleCondition("JUMP");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::J))
		{
			character->handleCondition("ROLL");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I))
		{
			character->handleCondition("ATTACK_1");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O))
		{
			character->handleCondition("ATTACK_2");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K))
		{
			character->handleCondition("ULTIMATE");
		}
	}
}
