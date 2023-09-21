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
		Ground tmp_ground{ 60, 60, float(i), 570.f };

		grounds.push_back(tmp_ground);
	}

	run();
}

void Game::update()
{
	for (auto const& ground : grounds)
	{
		if (isColliding(ground))
		{
			m_player.setCanJump(true);
		}
	}

	m_player.update(m_deltaTime);
}

void Game::render()
{
	m_window.clear();

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



bool Game::isColliding(const Ground& ground)
{
	float groundHalfSizeX = ground.getBounds().getSize().x / 2.f;
	float groundHalfSizeY = ground.getBounds().getSize().y / 2.f;
	float groundPositionX = ground.getBounds().getPosition().x + groundHalfSizeX;
	float groundPositionY = ground.getBounds().getPosition().y + groundHalfSizeY;

	float playerHalfSizeX = m_player.getBounds().getSize().x / 2.f;
	float playerHalfSizeY = m_player.getBounds().getSize().y / 2.f;
	float playerPositionX = m_player.getBounds().getPosition().x + playerHalfSizeX;
	float playerPositionY = m_player.getBounds().getPosition().y + playerHalfSizeY;

	float deltaX = groundPositionX - playerPositionX;
	float deltaY = groundPositionY - playerPositionY;

	float intersectX = abs(deltaX) - (groundHalfSizeX + playerHalfSizeX);
	float intersectY = abs(deltaY) - (groundHalfSizeY + playerHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f) {

		if (intersectX > intersectY) {
			if (deltaX > 0.f) {
				m_player.collisionDirectionX = 1.0f;
			}
			else {
				m_player.collisionDirectionX = -1.0f;
			}
			m_player.collisionDirectionY = 0.f;
		}
		else {
			if (deltaY > 0.f) {
				m_player.collisionDirectionY = 1.0f;
			}
			else {
				m_player.collisionDirectionY = -1.0f;
			}
			m_player.collisionDirectionX = 0.f;
		}

		return true;
	}

	return false;
}