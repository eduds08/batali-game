#include "Game.h"

Game::Game()
	: m_stateContext{new MainMenuState{m_window}}
{
	//m_window.setKeyRepeatEnabled(false);
	::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE);
	run();
}

Game::~Game()
{
	if (m_stateContext)
	{
		delete m_stateContext;
		m_stateContext = nullptr;
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
				// Quit animation thread
				m_stateContext->setCurrentState(constants::quittingPlaying);

				m_window.close();
			}
		}

		update();
		render();
	}
}

void Game::update()
{
	// If on playing state and the user press Escape button, it changes to MainMenuState
	if (m_stateContext->getCurrentState() == constants::playingState)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
		{
			// Quit animation thread
			m_stateContext->setCurrentState(constants::quittingPlaying);

			// Changes to MainMenuState
			delete m_stateContext;
			m_stateContext = new MainMenuState(m_window);
		}
	}

	m_stateContext->update();

	// The user pressed button "Singleplayer" or "Multiplayer"
	if (m_stateContext->getCurrentState() == constants::singleplayerTransition || m_stateContext->getCurrentState() == constants::multiplayerTransition)
	{
		// Singleplayer or multiplayer
		if (m_stateContext->getCurrentState() == constants::singleplayerTransition)
		{
			delete m_stateContext;
			m_stateContext = new PlayingState(m_window, m_deltaTime, false);
		}
		else
		{
			delete m_stateContext;
			m_stateContext = new PlayingState(m_window, m_deltaTime, true);
		}
	}

	// Press the button to close the game
	if (m_stateContext->getCurrentState() == constants::exitingState)
	{
		delete m_stateContext;
		m_stateContext = nullptr;
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear();
	if (m_stateContext)
	{
		m_stateContext->render();
	}
	m_window.display();
}
