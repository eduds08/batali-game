#include "Game.h"

Game::Game()
{
	m_menuContext = new MainMenuState(m_window, m_deltaTime);
	run();
}

Game::~Game()
{
	if (m_menuContext)
	{
		delete m_menuContext;
		m_menuContext = nullptr;
	}
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
				if (m_menuContext->getCurrentState() == "playing")
				{
					dynamic_cast<PlayingState*>(m_menuContext)->setOnPlayingState(false);
				}
				m_window.close();
			}
		}

		update();
		render();
	}
}

void Game::update()
{
	if (m_menuContext->getCurrentState() == "main")
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
		{
			delete m_menuContext;
			m_menuContext = new PlayingState(m_window, m_deltaTime);
		}
	}
	if (m_menuContext->getCurrentState() == "playing")
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
		{
			dynamic_cast<PlayingState*>(m_menuContext)->setOnPlayingState(false);
			delete m_menuContext;
			m_menuContext = new MainMenuState(m_window, m_deltaTime);
		}
	}

	m_menuContext->update();
}

void Game::render()
{
	m_window.clear();
	m_menuContext->render();
	m_window.display();
}
