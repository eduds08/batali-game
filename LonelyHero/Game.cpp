#include "Game.h"

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

	for (int i = 0; i < 600; i += 60)
	{
		Ground tmp_ground{ 60, 60, 1, 0.1f, float(i), 540.f };

		grounds.push_back(tmp_ground);
		groundsBound.push_back(tmp_ground.getBounds());
	}

	run();
}

void Game::update()
{
	m_player.update(m_deltaTime);

	for (auto const& groundBound : groundsBound)
	{
		m_player.checkCollisionWith(groundBound);
	}
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
		if (m_deltaTime > 1.f / 60.f)
		{
			m_deltaTime = 1.f / 60.f;
		}

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
