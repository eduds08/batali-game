#include "Game.h"

bool Game::isGameRunning = true;

Game::Game()
{
	init();
}

void Game::init()
{
	enemies.emplace_back(Enemy{ enemyFirstPosition, m_player.getPosition() });
	//enemies.emplace_back(Enemy{ sf::Vector2f{400.f, 240.f}, m_player.getPosition() });
	
	loadAndCreateMap("./map.txt");
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

	// Quit thread
	animationThread.join();
}

void Game::update()
{
	updateCollision();

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
		//m_window.draw(enemy.getShape());
		m_window.draw(enemy.getSprite());
		//m_window.draw(enemy.getAttackHitbox());
	}

	m_window.draw(m_player.getAttackHitbox());
	

	for (auto& ground : grounds)
	{
		if (ground.getSprite().getPosition().x <= m_horizontalViewLimitRight && ground.getSprite().getPosition().x >= m_horizontalViewLimitLeft
			&& ground.getSprite().getPosition().y >= m_verticalViewLimitTop && ground.getSprite().getPosition().y <= m_verticalViewLimitBottom)
		{
			m_window.draw(ground.getSprite());
		}
	}

	m_window.display();
}

void Game::updateCollision()
{
	for (auto& enemy : enemies)
	{
		enemy.resetCollidingHorizontally();
	}

	m_player.resetCollidingHorizontally();

	for (auto& ground : grounds)
	{
		if (m_player.isCollidingWith(ground.getSprite()))
		{
			m_player.handleCollision();
			m_player.handleKnockbackVelocity();
			m_player.updateCanJump();
		}

		for (auto& enemy : enemies)
		{
			if (enemy.isCollidingWith(ground.getSprite()))
			{
				enemy.handleCollision();
				enemy.handleKnockbackVelocity();
				enemy.updateCanJump();
			}
		}
	}

	for (auto& enemy : enemies)
	{
		if (enemy.getShape().getGlobalBounds().intersects((m_player.getAttackHitbox().getGlobalBounds())))
		{
			float attackDirection = m_player.getPosition().x - enemy.getPosition().x;
			enemy.takeDamage(m_deltaTime, attackDirection);
			if (enemy.getInDamageCooldown() && !enemy.isDead())
			{
				enemy.knockbackMove(m_deltaTime, attackDirection);
			}
		}

		if (m_player.getShape().getGlobalBounds().intersects((enemy.getAttackHitbox().getGlobalBounds())))
		{
			float attackDirection = enemy.getPosition().x - m_player.getPosition().x;
			m_player.takeDamage(m_deltaTime, attackDirection);
			if (m_player.getInDamageCooldown() && !m_player.isDead())
			{
				m_player.knockbackMove(m_deltaTime, attackDirection);
			}
		}
	}
}

void Game::updateView()
{
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);

	m_horizontalViewLimitRight = m_view.getCenter().x + m_view.getSize().x / 2.f + tileSizeF;
	m_horizontalViewLimitLeft = m_view.getCenter().x - m_view.getSize().x / 2.f - tileSizeF;

	m_verticalViewLimitTop = m_view.getCenter().y - m_view.getSize().y / 2.f - tileSizeF;
	m_verticalViewLimitBottom = m_view.getCenter().y + m_view.getSize().y / 2.f + tileSizeF;
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
