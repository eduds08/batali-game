#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow& window, float& deltaTime)
	: StateContext{ window }
	, m_deltaTime{ deltaTime }
{
	m_currentState = "playing";

	if (!twoPlayers)
	{
		players.pop_back();
	}
	else
	{
		enemies.clear();
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

		m_playerHealthBar.update();

		if (twoPlayers)
		{
			m_player2HealthBar.update();
		}
		else
		{
			m_enemyHealthBar.update();
		}

		for (auto& player : players)
		{
			player.update(m_deltaTime);
		}

		for (auto& enemy : enemies)
		{
			enemy.update(m_deltaTime);
		}

		updateView();
	}
}

void PlayingState::render()
{
	m_window.draw(wallpaper);

	for (auto& player : players)
	{
		m_window.draw(player.getShape());
		m_window.draw(player.getSprite());
	}

	for (auto& enemy : enemies)
	{
		m_window.draw(enemy.getShape());
		m_window.draw(enemy.getSprite());
		m_window.draw(enemy.getAttackHitbox());
	}

	for (auto& player : players)
	{
		m_window.draw(player.getAttackHitbox());
	}
	

	for (auto& ground : grounds)
	{
		// Only draw the tiles that are inside the view
		if (ground.getSprite().getPosition().x <= m_rightViewLimit && ground.getSprite().getPosition().x >= m_leftViewLimit
			&& ground.getSprite().getPosition().y >= m_topViewLimit && ground.getSprite().getPosition().y <= m_bottomViewLimit)
		{
			m_window.draw(ground.getSprite());
		}
	}

	m_window.draw(m_playerHealthBar.getSprite());
	if (twoPlayers)
	{
		m_window.draw(m_player2HealthBar.getSprite());
	}
	else
	{
		m_window.draw(m_enemyHealthBar.getSprite());
	}
	
}

void PlayingState::updateCollision()
{
	// We reset isCollidingHorizontally to false for all entities, so when isColliding() is called, if the entity collides in the x-direction, it will be true.
	// If doesn't collide, it remains false.

	for (auto& player : players)
	{
		player.setIsCollidingHorizontally(false);
	}
	
	for (auto& enemy : enemies)
	{
		enemy.setIsCollidingHorizontally(false);
	}

	// Entities' collision with tiles
	for (auto& ground : grounds)
	{
		// Player's collision
		for (auto& player : players)
		{
			updateEntityCollisionWithGrounds(player, ground);
		}

		// Enemies' collision
		for (auto& enemy : enemies)
		{
			updateEntityCollisionWithGrounds(enemy, ground);
		}
	}

	if (twoPlayers)
	{
		if (players[1].getShape().getGlobalBounds().intersects((players[0].getAttackHitbox().getGlobalBounds())) && !players[1].isDying())
		{
			handleEntityAttacked(players[0], players[1]);
		}

		if (players[0].getShape().getGlobalBounds().intersects((players[1].getAttackHitbox().getGlobalBounds())) && !players[0].isDying())
		{
			handleEntityAttacked(players[1], players[0]);
		}
	}

	// Checks if the an entity was attacked by another entity
	for (auto& enemy : enemies)
	{
		// Enemy attacked by player
		if (enemy.getShape().getGlobalBounds().intersects((players[0].getAttackHitbox().getGlobalBounds())) && !enemy.isDying())
		{
			handleEntityAttacked(players[0], enemy);
		}

		// Player attacked by an enemy
		if (players[0].getShape().getGlobalBounds().intersects((enemy.getAttackHitbox().getGlobalBounds())) && !players[0].isDying())
		{
			handleEntityAttacked(enemy, players[0]);
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
		for (auto& ground : grounds)
		{
			updateEntityCollisionWithGrounds(attackedEntity, ground);
		}
		attackedEntity.knockbackMove(m_deltaTime, attackDirection);
	}
}

void PlayingState::updateView()
{
	m_view.setCenter(players[0].getPosition());

	m_window.setView(m_view);

	m_rightViewLimit = m_view.getCenter().x + m_view.getSize().x / 2.f + tileSizeF;
	m_leftViewLimit = m_view.getCenter().x - m_view.getSize().x / 2.f - tileSizeF;

	m_topViewLimit = m_view.getCenter().y - m_view.getSize().y / 2.f - tileSizeF;
	m_bottomViewLimit = m_view.getCenter().y + m_view.getSize().y / 2.f + tileSizeF;

	m_playerHealthBar.setPosition(m_view.getCenter() - m_view.getSize() / 2.f);

	if (twoPlayers)
	{
		m_player2HealthBar.setPosition(m_view.getCenter() + sf::Vector2f{m_view.getSize().x / 2.f, -1.f * m_view.getSize().y / 2.f});
	}
	else
	{
		m_enemyHealthBar.setPosition(m_view.getCenter() + sf::Vector2f{m_view.getSize().x / 2.f, -1.f * m_view.getSize().y / 2.f});
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
				grounds.emplace_back(Ground{ sf::Vector2f{x * tileSizeF + tileSizeF / 2.f, y * tileSizeF + tileSizeF / 2.f}, tileId,  "./tiles/" + tileId + ".png"});
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
	while (m_onPlayingState)
	{
		if (!m_onPause)
		{
			// If there isn't a thread sleep or if the milliseconds time is too short, the animation will run so fast that it bugs and doesn't display sprites correctly
			std::this_thread::sleep_for(std::chrono::milliseconds(75));

			for (auto& player : players)
			{
				if (!player.isDead())
				{
					player.updateAnimation();
				}
			}

			for (auto& enemy : enemies)
			{
				if (!enemy.isDead())
				{
					enemy.updateAnimation();
				}
			}
		}
	}
}
