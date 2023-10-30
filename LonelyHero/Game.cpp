#include "Game.h"

Game::Game()
{
	init();
}

Game::~Game()
{
	if (m_menuContext)
	{
		delete m_menuContext;
		m_menuContext = nullptr;
	}
}

void Game::init()
{
	m_menuContext = new MainMenuState(m_window, m_deltaTime);
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
				if (m_currentState == "playing")
				{
					dynamic_cast<PlayingState*>(m_menuContext)->isGameRunning = false;
				}
				m_window.close();
			}
		}

		if (m_currentState == "main")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
			{
				m_currentState = "playing";
				delete m_menuContext;
				m_menuContext = new PlayingState(m_window, m_deltaTime);
			}
		}
		if (m_currentState == "playing")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
			{
				m_currentState = "main";
				dynamic_cast<PlayingState*>(m_menuContext)->isGameRunning = false;
				delete m_menuContext;
				m_menuContext = new MainMenuState(m_window, m_deltaTime);
			}
		}

		m_menuContext->update();
		m_menuContext->render();
	}
}

//void Game::update()
//{
//}
//
//void Game::render()
//{
//}
