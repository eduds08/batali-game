#include "PrincipalTemporario.h"

PrincipalTemporario::PrincipalTemporario()
{
	menuState = nullptr;
	playingState = nullptr;
	init();
}

PrincipalTemporario::~PrincipalTemporario()
{
	if (menuState)
	{
		delete menuState;
		menuState = nullptr;
	}
	if (playingState)
	{
		delete playingState;
		playingState = nullptr;
	}
}

void PrincipalTemporario::init()
{
	menuState = new MainMenu();
	run();
}

void PrincipalTemporario::run()
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
				if (playingState)
				{
					playingState->isGameRunning = false;
				}
				m_window.close();
			}
		}

		update();
		render();
	}
}

void PrincipalTemporario::update()
{
	if (menuState)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
		{
			delete menuState;
			menuState = nullptr;
			playingState = new Game(m_deltaTime);
		}
	}

	if (playingState)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
		{
			playingState->isGameRunning = false;
			delete playingState;
			playingState = nullptr;
			menuState = new MainMenu();
			m_window.setView(menuState->viewTemp);
		}
		else 
		{
			playingState->update();
			m_window.setView(playingState->m_view);
		}
	}
}

void PrincipalTemporario::render()
{

	m_window.clear();
	

	if (menuState)
	{
		m_window.draw(menuState->buttonsRectangle[0]);
		m_window.draw(menuState->buttonsText[0]);
	}
	if (playingState)
	{
		m_window.draw(playingState->m_player.getShape());
		m_window.draw(playingState->m_player.getSprite());

		for (auto& enemy : playingState->enemies)
		{
			m_window.draw(enemy.getShape());
			m_window.draw(enemy.getSprite());
			m_window.draw(enemy.getAttackHitbox());
		}

		m_window.draw(playingState->m_player.getAttackHitbox());
		

		for (auto& ground : playingState->grounds)
		{
			// Only draw the tiles that are inside the view
			if (ground.getSprite().getPosition().x <= playingState->m_rightViewLimit && ground.getSprite().getPosition().x >= playingState->m_leftViewLimit
				&& ground.getSprite().getPosition().y >= playingState->m_topViewLimit && ground.getSprite().getPosition().y <= playingState->m_bottomViewLimit)
			{
				m_window.draw(ground.getSprite());
			}
		}

		m_window.draw(playingState->m_playerHealthBar.getSprite());
		m_window.draw(playingState->m_enemyHealthBar.getSprite());
	}

	m_window.display();
}
