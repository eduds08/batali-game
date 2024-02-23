#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime, bool twoPlayers)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
	, m_twoPlayers{ twoPlayers }
{
	m_currentState = constants::playingState;

	m_players.emplace_back(std::make_shared<FireKnight>(leftCharacterFirstPosition));
	m_healthBars.emplace_back(HealthBarUI("leftHealthBar", "./assets/ui/leftHealthBar.png", &m_players[0]->getHp()));

	if (m_twoPlayers)
	{
		m_players.emplace_back(std::make_shared<WindHashashin>(rightCharacterFirstPosition, 2));
		m_healthBars.emplace_back(HealthBarUI("rightHealthBar", "./assets/ui/rightHealthBar.png", &m_players[1]->getHp()));
	}
	else
	{
		m_bots.emplace_back(std::make_unique<WindHashashin>(rightCharacterFirstPosition, 0, true, m_players[0]));
		m_healthBars.emplace_back(HealthBarUI("rightHealthBar", "./assets/ui/rightHealthBar.png", &m_bots[0]->getHp()));
	}

	temp.loadFromFile("./assets/landmark.png");
	wallpaper.setTexture(temp);

	loadAndCreateMap("./map/map.txt");

	animationThread = std::thread(&PlayingState::updateTexturesAndAnimations, this);

	m_view = m_window.getDefaultView();
	m_view.zoom(0.5f);
	m_window.setView(m_view);
}

PlayingState::~PlayingState()
{
	animationThread.join();
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

		for (auto& healthBar : m_healthBars)
		{
			healthBar.update();
		}

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
	m_window.draw(wallpaper);

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

	for (auto& healthBar : m_healthBars)
	{
		m_window.draw(healthBar.getSprite());
	}

	sf::RectangleShape tempooo{sf::Vector2f(1.f, 1.f)};
	tempooo.setPosition(0.f, 0.f);
	tempooo.setFillColor(sf::Color::Green);
	m_window.draw(tempooo);
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
	float attackDirection = attackingEntity.getPosition().x - attackedEntity.getPosition().x;

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
	if (!m_twoPlayers)
	{
		m_view.setCenter(m_players[0]->getPosition());
	}
	else
	{
		m_view.setCenter(m_view.getSize().x / 2.f, 350.f);
	}

	m_window.setView(m_view);

	m_rightViewLimit = m_view.getCenter().x + m_view.getSize().x / 2.f + tileSizeF;
	m_leftViewLimit = m_view.getCenter().x - m_view.getSize().x / 2.f - tileSizeF;

	m_topViewLimit = m_view.getCenter().y - m_view.getSize().y / 2.f - tileSizeF;
	m_bottomViewLimit = m_view.getCenter().y + m_view.getSize().y / 2.f + tileSizeF;

	for (auto& healthBar : m_healthBars)
	{
		if (healthBar.getDirection() == "left")
		{
			healthBar.setPosition(m_view.getCenter() - m_view.getSize() / 2.f);
		}
		else
		{
			healthBar.setPosition(m_view.getCenter() + sf::Vector2f{m_view.getSize().x / 2.f, -1.f * m_view.getSize().y / 2.f});
		}
	}
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
