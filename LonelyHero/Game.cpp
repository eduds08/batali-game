#include "Game.h"
#include <iostream>

Game::Game()
{
	m_window.setVerticalSyncEnabled(true);
	init();
}

Game::~Game()
{
}

void Game::init()
{

	for (int i = 30; i < 600; i += 60)
	{
		Ground tmp_ground{ 60, 60, 60, 60, static_cast<float>(i), 570.f };

		grounds.push_back(tmp_ground);
	}

	Ground g1{ 60, 60, 60, 60, 90.f, 510.f };

	grounds.push_back(g1);

	Ground g2{ 60, 60, 60, 60, 150.f, 450.f };

	grounds.push_back(g2);

	run();
}

void Game::update()
{
	m_player.update(m_deltaTime);

	for (auto& ground : grounds)
	{
		if (isColliding(ground, 0.f))
		{
			m_player.onCollision(m_player.collisionDirectionX, m_player.collisionDirectionY);
		}
	}
}

void Game::render()
{
	m_window.clear();

	//m_window.draw(m_player.getShape());
	m_window.draw(m_player.getSprite());

	for (auto const& ground : grounds)
	{
		m_window.draw(ground.getSprite());
	}

	m_window.display();
}

void Game::run()
{
	while (m_window.isOpen())
	{		
		m_deltaTime = Game::clock.restart().asSeconds();

		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		update();
		render();
	}
}



bool Game::isColliding(Ground& ground, float p)
{
	float groundHalfSizeX = ground.getSize().x / 2.f;
	float groundHalfSizeY = ground.getSize().y / 2.f;
	float groundPositionX = ground.getPosition().x;
	float groundPositionY = ground.getPosition().y;

	float playerHalfSizeX = m_player.getSize().x / 2.f;
	float playerHalfSizeY = m_player.getSize().y / 2.f;
	float playerPositionX = m_player.getPosition().x;
	float playerPositionY = m_player.getPosition().y;

	float deltaX = groundPositionX - playerPositionX;
	float deltaY = groundPositionY - playerPositionY;

	float intersectX = abs(deltaX) - (groundHalfSizeX + playerHalfSizeX);
	float intersectY = abs(deltaY) - (groundHalfSizeY + playerHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f) 
	{

		float push = std::min(std::max(p, 0.f), 1.f);

		if (intersectX > intersectY) {

			if (deltaX > 0.f) 
			{
				m_player.moveTmp(intersectX, 0.f);
				m_player.collisionDirectionX = 1.0f;
			}
			else 
			{
				m_player.moveTmp(-intersectX, 0.f);
				m_player.collisionDirectionX = -1.0f;
			}
			m_player.collisionDirectionY = 0.f;
		}
		else 
		{
			if (deltaY > 0.f) 
			{
				m_player.moveTmp(0.f, intersectY);
				m_player.collisionDirectionY = 1.0f;
			}
			else 
			{
				m_player.moveTmp(0.f, -intersectY);
				m_player.collisionDirectionY = -1.0f;
			}
			m_player.collisionDirectionX = 0.f;
		}

		return true;
	}

	return false;
}