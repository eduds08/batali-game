#include "Game.h"

Game::Game()
	: m_stateContext{new MainMenuState{m_window}}
{
	// Open maximized window
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
				m_stateContext->setCurrentState(EXIT_PLAYING);

				m_window.close();
			}

			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_stateContext != nullptr)
				{
					m_stateContext->setPressedKey(m_event.key.scancode);
				}
			}
		}

		update();
		render();
	}
}

void Game::update()
{
	// If on playing state and the user press Escape button, it changes to MainMenuState
	if (m_stateContext->getCurrentState() == PLAYING_STATE)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
		{
			// Quit animation thread
			m_stateContext->setCurrentState(EXIT_PLAYING);

			// Changes to MainMenuState
			delete m_stateContext;
			m_stateContext = new MainMenuState(m_window);
		}
	}

	m_stateContext->update();

	// The user pressed button "Singleplayer" or "Multiplayer"
	if (m_stateContext->getCurrentState() == MENU_TO_SINGLEPLAYER || m_stateContext->getCurrentState() == MENU_TO_MULTIPLAYER)
	{
		// Singleplayer or multiplayer
		if (m_stateContext->getCurrentState() == MENU_TO_SINGLEPLAYER)
		{
			delete m_stateContext;
			m_stateContext = new CharacterSelectionState(m_window, "singleplayer");
		}
		else
		{
			delete m_stateContext;
			m_stateContext = new CharacterSelectionState(m_window, "multiplayer");
		}
	}

	if (m_stateContext->getCurrentState() == CHARACTER_SELECTION_TO_SINGLEPLAYER)
	{
		std::string firstCharacter = dynamic_cast<CharacterSelectionState*>(m_stateContext)->m_chosenCharacters[0];
		std::string secondCharacter = dynamic_cast<CharacterSelectionState*>(m_stateContext)->m_chosenCharacters[1];

		delete m_stateContext;
		m_stateContext = new PlayingState(m_window, m_deltaTime, false, firstCharacter, secondCharacter);
	}

	if (m_stateContext->getCurrentState() == CHARACTER_SELECTION_TO_MULTIPLAYER)
	{
		std::string firstCharacter = dynamic_cast<CharacterSelectionState*>(m_stateContext)->m_chosenCharacters[0];
		std::string secondCharacter = dynamic_cast<CharacterSelectionState*>(m_stateContext)->m_chosenCharacters[1];

		delete m_stateContext;
		m_stateContext = new PlayingState(m_window, m_deltaTime, true, firstCharacter, secondCharacter);
	}

	if (m_stateContext->getCurrentState() == CHARACTER_SELECTION_STATE)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
		{
			// Quit animation thread
			m_stateContext->setCurrentState(EXIT_PLAYING);

			// Changes to MainMenuState
			delete m_stateContext;
			m_stateContext = new MainMenuState(m_window);
		}
	}

	if (m_stateContext->getCurrentState() == CHARACTER_SELECTION_RESET)
	{
		std::string chosenGamemode = dynamic_cast<CharacterSelectionState*>(m_stateContext)->getChosenGamemode();

		delete m_stateContext;
		m_stateContext = new CharacterSelectionState(m_window, chosenGamemode);
	}

	// Press the button to close the game
	if (m_stateContext->getCurrentState() == EXIT_GAME)
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
