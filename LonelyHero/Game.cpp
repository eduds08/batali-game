#include "Game.h"

#include <iostream>

bool Game::isRunning = true;

Game::Game()
{
	init();
}

Game::~Game()
{
}

void Game::init()
{
	m_window.setView(m_view);
	loadAndCreateMap("./map.txt");
	animationThread = std::thread(&Game::updateTexturesAndAnimations, this);
	//collisionThread = std::thread(&Game::updateCollision, this);
	run();
}

void Game::update()
{
	m_player.update(m_deltaTime);
	m_enemy.update(m_deltaTime);

	clock2Time = clock2.getElapsedTime().asSeconds();
	if (clock2Time > 0.55f && m_enemy.justHitted)
	{
		m_enemy.justHitted = false;
	}

	updateCollision();

	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_player.getShape());
	m_window.draw(m_player.getSprite());

	m_window.draw(m_enemy.getShape());
	m_window.draw(m_enemy.getSprite());

	m_window.draw(m_player.getHitbox());
	m_window.draw(m_enemy.getHitbox());

	float horizontalLimitRight = m_view.getCenter().x + m_view.getSize().x / 2.f + 16.f * 3.f;
	float horizontalLimitLeft = m_view.getCenter().x - m_view.getSize().x / 2.f - 16.f * 3.f;

	float verticalLimitTop = m_view.getCenter().y - m_view.getSize().y / 2.f - 16.f * 3.f;
	float verticalLimitBottom = m_view.getCenter().y + m_view.getSize().y / 2.f + 16.f * 3.f;

	for (auto& ground : grounds)
	{
		if (ground.getSprite().getPosition().x <= horizontalLimitRight && ground.getSprite().getPosition().x >= horizontalLimitLeft
			&& ground.getSprite().getPosition().y >= verticalLimitTop && ground.getSprite().getPosition().y <= verticalLimitBottom)
		{
			m_window.draw(ground.getSprite());
		}
	}

	m_window.display();
}

void Game::run()
{
	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();

		if (m_deltaTime > 1.f / 20.f)
		{
			m_deltaTime = { 1.f / 20.f };
		}

		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				Game::isRunning = false;
				m_window.close();
			}
		}

		update();
		render();
	}

	animationThread.join();
	//collisionThread.join();
}

void Game::updateCollision()
{
	//while (Game::isRunning)
	//{
		for (auto& ground : grounds)
		{
			if (m_player.isCollidingWith(ground.getSprite()))
			{
				m_player.handleCollision();
				m_player.checkIfCanJump();
			}
			
			
			if (m_enemy.isCollidingWith(ground.getSprite()))
			{
				m_enemy.handleCollision();
			}
		}

		if (m_enemy.getShape().getGlobalBounds().intersects((m_player.getHitbox().getGlobalBounds())) && !m_enemy.justHitted)
		{
			clock2.restart();
			m_enemy.justHitted = true;
			m_enemy.hp -= 25;
			m_enemy.getShape().move(70000.f * m_deltaTime, 0.f);
		}
		//if (m_player.getShape().getGlobalBounds().intersects((m_enemy.getHitbox().getGlobalBounds())) && !m_player.justHitted)
		//{
		// 
		//	m_player.justHitted = true;
		//}
	//}
}

void Game::loadAndCreateMap(const std::string& mapFilePath)
{
	std::fstream mapFile{ mapFilePath, std::ios::in };
	std::string row{};

	int x{ 0 };
	int y{ 0 };

	std::string a{};

	while (std::getline(mapFile, row))
	{
		for (int i = 0; i < 100; i++)
		{
			mapFile >> a;
			if (a != "0")
			{
				grounds.emplace_back(Ground{ 16, 16, sf::Vector2f{x * 16.f + 8.f, y * 16.f + 8.f}, a,  "./tiles/" + a + ".png" });
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
	while (Game::isRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		animationMutex.lock();
		if (!m_player.dead)
		{
			m_player.updateAnimation();
		}

		if (!m_enemy.dead)
		{
			m_enemy.updateAnimation();
		}
		animationMutex.unlock();
	}

}
