#include "MenuContext.h"

MenuContext::MenuContext(sf::RenderWindow& window, float& deltaTime)
	: m_window{window}
	, m_deltaTime{deltaTime}
{
}

//MenuContext::~MenuContext()
//{
	/*if (menuState)
	{
		delete menuState;
		menuState = nullptr;
	}
	if (playingState)
	{
		delete playingState;
		playingState = nullptr;
	}*/
//
//void MenuContext::init()
//{
//	//menuState = new MainMenuState();
//	//run();
//}

//void MenuContext::run()
//{
//	while (m_window.isOpen())
//	{
//		m_deltaTime = m_deltaTimeClock.restart().asSeconds();
//
//		// Fix bug where FPS increases a lot when dragging the window
//		if (m_deltaTime > 1.f / 20.f)
//		{
//			m_deltaTime = { 1.f / 20.f };
//		}
//
//		while (m_window.pollEvent(m_event))
//		{
//			if (m_event.type == sf::Event::Closed)
//			{
//				//if (m_currentState == "playing")
//				//{
//				//	dynamic_cast<PlayingState*>(this)->isGameRunning = false;
//				//	//playingState->isGameRunning = false;
//				//}
//				m_window.close();
//			}
//		}
//
//		if (m_currentState == "main")
//		{
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
//			{
//				m_currentState = "playing";
//			}
//		}
//		if (m_currentState == "playing")
//		{
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
//			{
//				m_currentState = "main";
//			}
//		}
//
//		update();
//		render();
//	}
//}

//void MenuContext::update()
//{
//	if (m_currentState == "main")
//	{
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
//		{
//			/*delete menuState;
//			menuState = nullptr;
//			playingState = new PlayingState();*/
//			m_currentState = "playing";
//		}
//		else
//		{
//			dynamic_cast<MainMenuState*>(this)->update();
//		}
//	}
//
//
//	if (m_currentState == "playing");
//	{
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
//		{
//			m_currentState = "main";
//			dynamic_cast<PlayingState*>(this)->isGameRunning = false;
//			/*delete playingState;
//			playingState = nullptr;
//			menuState = new MainMenuState();*/
//			
//			m_window.setView(dynamic_cast<MainMenuState*>(this)->viewTemp);
//		}
//		else 
//		{
//			dynamic_cast<PlayingState*>(this)->update();
//		}
//	}
//}
//
//void MenuContext::render()
//{
//
//	m_window.clear();
//	
//
//	if (m_currentState == "main")
//	{
//		m_window.draw(dynamic_cast<MainMenuState*>(this)->buttonsRectangle[0]);
//		m_window.draw(dynamic_cast<MainMenuState*>(this)->buttonsText[0]);
//	}
//
//	if (m_currentState == "playing")
//	{
//		dynamic_cast<PlayingState*>(this)->render();
//	}
//
//	m_window.display();
//}
