#include "MainMenuState.h"
#include <iostream>
MainMenuState::MainMenuState(sf::RenderWindow& window) :
	MenuContext{ window }
{
	m_currentState = "main";

	initButton("Play", 0);
	initButton("Options", 1);
	initButton("Exit", 2);

	m_view.setSize(sf::Vector2f{screenWidth, screenHeight});
	m_view.setCenter(m_view.getSize() / 2.f);

	m_window.setView(m_view);
}

void MainMenuState::initButton(const std::string& text, int position)
{
	sf::RectangleShape buttonShape{ sf::Vector2f{300.f, 50.f} };
	buttonShape.setOrigin(buttonShape.getSize() / 2.f);
	buttonShape.setPosition(sf::Vector2f{ screenWidth / 2.f, screenHeight / 2.f + position * 100.f });
	buttonShape.setOutlineColor(sf::Color::Red);
	buttonShape.setOutlineThickness(1.f);

	sf::Text buttonText{ text, m_font };
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.f, buttonText.getLocalBounds().height / 2.f);

	buttonText.setFillColor(sf::Color::Blue);
	buttonText.setPosition(buttonShape.getPosition());

	buttonsRectangle.emplace_back(buttonShape);
	buttonsText.emplace_back(buttonText);
}

void MainMenuState::update()
{
	delayTime = delayClock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && delayTime > 0.15f)
	{
		++m_onHoverButton;
		if (m_onHoverButton >= buttonsRectangle.size())
		{
			m_onHoverButton = buttonsRectangle.size() - 1;
		}
		delayClock.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && delayTime > 0.15f)
	{
		--m_onHoverButton;
		if (m_onHoverButton < 0)
		{
			m_onHoverButton = 0;
		}
		delayClock.restart();
	}

	for (int i = 0; i < buttonsRectangle.size(); ++i)
	{
		if (i == m_onHoverButton)
		{
			buttonsRectangle[i].setOutlineColor(sf::Color::Green);
			buttonsRectangle[i].setFillColor(sf::Color::Magenta);
		}
		else 
		{
			buttonsRectangle[i].setOutlineColor(sf::Color::Red);
			buttonsRectangle[i].setFillColor(sf::Color::Yellow);
		}
	}
}

void MainMenuState::render()
{
	for (const auto& buttonShape : buttonsRectangle)
	{
		m_window.draw(buttonShape);
	}
	for (const auto& buttonText : buttonsText)
	{
		m_window.draw(buttonText);
	}
}

void MainMenuState::pressButton()
{
	if (m_onHoverButton == 0)
	{
		m_currentState = "playing";
	}
	else if (m_onHoverButton == 2)
	{
		m_currentState = "exiting";
	}
}
