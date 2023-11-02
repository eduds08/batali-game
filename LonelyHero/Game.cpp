#include "Game.h"

Game::Game()
	: m_stateContext{new MainMenuState{m_window}}
{
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
				if (m_stateContext->getCurrentState() == "playing")
				{
					dynamic_cast<PlayingState*>(m_stateContext)->setOnPlayingState(false);
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
	// If on playing state and the user press Escape button, it changes to MainMenuState
	if (m_stateContext->getCurrentState() == "playing")
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
		{
			// To quit animation thread
			dynamic_cast<PlayingState*>(m_stateContext)->setOnPlayingState(false);

			delete m_stateContext;
			m_stateContext = new MainMenuState(m_window);
		}
	}

	m_stateContext->update();

	// The user pressed button "Play"
	if (m_stateContext->getCurrentState() == "transitionToPlaying")
	{
		delete m_stateContext;
		m_stateContext = new PlayingState(m_window, m_deltaTime);
	}

	// Press the button to close the game
	if (m_stateContext->getCurrentState() == "exiting")
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
