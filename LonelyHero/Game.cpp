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
		grounds.emplace_back(Ground{ 60, 60, sf::Vector2f{ static_cast<float>(i), 570.f } });
	}

	grounds.emplace_back(Ground{ 60, 60, sf::Vector2f{ 90.f, 510.f } });

	grounds.emplace_back(Ground{ 60, 60, sf::Vector2f{ 150.f, 450.f } });

	run();
}

void Game::update()
{
	m_player.update(m_deltaTime);

	for (auto& ground : grounds)
	{
		if (m_player.isColliding(ground.getSprite()))
		{
			m_player.onCollision();
			if (m_player.getCollisionDirection().y > 0.f)
			{
				m_player.setCanJump(true);
			}
		}
	}
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_player.getShape());
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
		m_deltaTime = m_clock.restart().asSeconds();

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
