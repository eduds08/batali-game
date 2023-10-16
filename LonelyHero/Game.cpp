#include "Game.h"

bool Game::isGameRunning = true;

Game::Game()
{
	init();
}

void Game::init()
{
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
	m_enemy.update(m_deltaTime);

	updateView();
}

void Game::render()
{
	m_window.clear();

	//m_window.draw(m_player.getShape());
	m_window.draw(m_player.getSprite());

	//m_window.draw(m_enemy.getShape());
	m_window.draw(m_enemy.getSprite());

	//m_window.draw(m_player.getAttackHitbox());
	//m_window.draw(m_enemy.getAttackHitbox());

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
	for (auto& ground : grounds)
	{
		if (m_player.isCollidingWith(ground.getSprite()))
		{
			m_player.handleCollision();
			m_player.handleKnockbackVelocity();
			m_player.updateCanJump();
		}

		if (m_enemy.isCollidingWith(ground.getSprite()))
		{
			m_enemy.handleCollision();
			m_enemy.handleKnockbackVelocity();
			m_enemy.updateCanJump();
		}
	}

	if (m_enemy.getShape().getGlobalBounds().intersects((m_player.getAttackHitbox().getGlobalBounds())))
	{
		m_enemy.takeDamage(m_deltaTime);
		if (m_enemy.getJustHitted() && !m_enemy.isDead())
		{
			m_enemy.knockbackMove(m_deltaTime);
		}
	}

	if (m_player.getShape().getGlobalBounds().intersects((m_enemy.getAttackHitbox().getGlobalBounds())))
	{
		m_player.takeDamage(m_deltaTime);
		if (m_player.getJustHitted() && !m_player.isDead())
		{
			m_player.knockbackMove(m_deltaTime);
		}
	}
}

void Game::updateView()
{
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);

	m_horizontalViewLimitRight = m_view.getCenter().x + m_view.getSize().x / 2.f + tileSize;
	m_horizontalViewLimitLeft = m_view.getCenter().x - m_view.getSize().x / 2.f - tileSize;

	m_verticalViewLimitTop = m_view.getCenter().y - m_view.getSize().y / 2.f - tileSize;
	m_verticalViewLimitBottom = m_view.getCenter().y + m_view.getSize().y / 2.f + tileSize;
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
		for (int i = 0; i < 100; i++)
		{
			mapFile >> tileId;
			if (tileId != "0")
			{
				grounds.emplace_back(Ground{ static_cast<int>(tileSize), static_cast<int>(tileSize), sf::Vector2f{x * tileSize + tileSize / 2.f, y * tileSize + tileSize / 2.f}, tileId,  "./tiles/" + tileId + ".png"});
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

		if (!m_enemy.isDead())
		{
			m_enemy.updateAnimation();
		}
	}
}
