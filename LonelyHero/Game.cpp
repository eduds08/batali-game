#include "Game.h"

#include <iostream>

bool Game::isGameRunning = true;

Game::Game()
{
	init();
}

void Game::init()
{
	enemies.emplace_back(Enemy{ enemyFirstPosition, m_player.getPosition() });

	m_playerHealthBar.setEntityHp(&m_player.getHp());
	m_enemyHealthBar.setEntityHp(&enemies[0].getHp());

	loadAndCreateMap("./map/map.txt");

	animationThread = std::thread(&Game::updateTexturesAndAnimations, this);

	run();
}

void Game::run()
{
	while (m_window.isOpen())
	{
		m_deltaTime = m_deltaTimeClock.restart().asSeconds();

		// Fix bug where FPS increases a lot when dragging the window
		if (m_deltaTime > 1.f / 20.f)
		{
			m_deltaTime = { 1.f / 20.f };
		}

		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				Game::isGameRunning = false;
				m_window.close();
			}
		}

		update();
		render();
	}

	// Quit animation thread
	animationThread.join();
}

void Game::update()
{
	updateCollision();

	m_playerHealthBar.updateHealthBar();
	m_enemyHealthBar.updateHealthBar();

	m_player.update(m_deltaTime);

	for (auto& enemy : enemies)
	{
		enemy.update(m_deltaTime);
	}

	updateView();
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_player.getShape());
	m_window.draw(m_player.getSprite());

	for (auto& enemy : enemies)
	{
		m_window.draw(enemy.getShape());
		m_window.draw(enemy.getSprite());
		m_window.draw(enemy.getAttackHitbox());
	}

	m_window.draw(m_player.getAttackHitbox());
	

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
	m_window.draw(m_enemyHealthBar.getSprite());

	m_window.display();
}

void Game::updateCollision()
{
	// We reset isCollidingHorizontally to false for all entities, so when isColliding() is called, if the entity collides in the x-direction, it will be true.
	// If doesn't collide, it remains false.
	m_player.setIsCollidingHorizontally(false);
	
	for (auto& enemy : enemies)
	{
		enemy.setIsCollidingHorizontally(false);
	}

	// Entities' collision with tiles
	for (auto& ground : grounds)
	{
		// Player's collision
		updateEntityCollisionWithGrounds(m_player, ground);

		// Enemies' collision
		for (auto& enemy : enemies)
		{
			updateEntityCollisionWithGrounds(enemy, ground);
		}
	}

	// Checks if the an entity was attacked by another entity
	for (auto& enemy : enemies)
	{
		// Enemy attacked by player
		if (enemy.getShape().getGlobalBounds().intersects((m_player.getAttackHitbox().getGlobalBounds())) && !enemy.isDying())
		{
			handleEntityAttacked(m_player, enemy);
		}

		// Player attacked by an enemy
		if (m_player.getShape().getGlobalBounds().intersects((enemy.getAttackHitbox().getGlobalBounds())) && !m_player.isDying())
		{
			handleEntityAttacked(enemy, m_player);
		}
	}
}

void Game::updateEntityCollisionWithGrounds(MovableEntity& entity, Ground& ground)
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

void Game::handleEntityAttacked(SwordEntity& attackingEntity, DamageEntity& attackedEntity)
{
	// If attackDirection is negative, the attack came from the right. Otherwise, it came from left.
	float attackDirection = attackingEntity.getPosition().x - attackedEntity.getPosition().x;

	attackedEntity.takeDamage(m_deltaTime, attackDirection, attackingEntity.getDamage());

	// Knockback of the attackedEntity. The attackedEntity will be pushed until it doesn't collide with the hitbox anymore or when it doesn't collide with a wall.
	while (attackedEntity.getShape().getGlobalBounds().intersects((attackingEntity.getAttackHitbox().getGlobalBounds())) && !attackedEntity.getIsCollidingHorizontally())
	{
		for (auto& ground : grounds)
		{
			updateEntityCollisionWithGrounds(attackedEntity, ground);
		}
		attackedEntity.knockbackMove(m_deltaTime, attackDirection);
	}
}

void Game::updateView()
{
	m_view.setCenter(m_player.getPosition());

	m_window.setView(m_view);

	m_rightViewLimit = m_view.getCenter().x + m_view.getSize().x / 2.f + tileSizeF;
	m_leftViewLimit = m_view.getCenter().x - m_view.getSize().x / 2.f - tileSizeF;

	m_topViewLimit = m_view.getCenter().y - m_view.getSize().y / 2.f - tileSizeF;
	m_bottomViewLimit = m_view.getCenter().y + m_view.getSize().y / 2.f + tileSizeF;

	m_playerHealthBar.setPosition(m_view.getCenter() - m_view.getSize() / 2.f);
	m_enemyHealthBar.setPosition(m_view.getCenter() + sf::Vector2f{m_view.getSize().x / 2.f, -1.f * m_view.getSize().y / 2.f});
}

void Game::loadAndCreateMap(const std::string& mapFilePath)
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
		y++;
	}

	mapFile.close();
}

void Game::updateTexturesAndAnimations()
{
	while (Game::isGameRunning)
	{
		// If there isn't a thread sleep or if the milliseconds time is too short, the animation will run so fast that it bugs and doesn't display sprites correctly
		std::this_thread::sleep_for(std::chrono::milliseconds(75));
		if (!m_player.isDead())
		{
			m_player.updateAnimation();
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
