#include "MainMenuState.h"
#include <iostream>
MainMenuState::MainMenuState(sf::RenderWindow& window) :
	StateContext{ window }
{
	m_currentState = "main";

	initButton("Play", 0);
	initButton("Settings", 1);
	initButton("Exit", 2);

	m_view.setSize(sf::Vector2f{ screenWidth, screenHeight });
	m_view.setCenter(m_view.getSize() / 2.f);

	m_window.setView(m_view);
}

void MainMenuState::initButton(const std::string& text, int position)
{
	buttons.emplace_back(ButtonUI{ sf::Vector2f{ screenWidth / 2.f, screenHeight / 2.f + position * 100.f }, "button", "./assets/ui/button.png" });

	sf::Text buttonText{ text, m_font };
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.f, buttonText.getLocalBounds().height / 2.f);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(buttons.back().getPosition());

	buttonsTexts.emplace_back(buttonText);
}

void MainMenuState::update()
{
	delayTime = delayClock.getElapsedTime().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && delayTime > 0.18f)
	{
		if (m_onHoverButton < buttons.size() - 1)
		{
			++m_onHoverButton;

			delayClock.restart();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && delayTime > 0.18f)
	{
		if (m_onHoverButton > 0)
		{
			--m_onHoverButton;

			delayClock.restart();
		}
	}

	for (size_t i = 0; i < buttons.size(); ++i)
	{
		buttons[i].update(i == m_onHoverButton);
		buttonsTexts[i].setPosition(buttons[i].getPosition());

		if (i == m_onHoverButton)
		{
			buttonsTexts[i].setPosition(buttons[i].getPosition() + sf::Vector2f{0.f, 2.f});
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))
	{
		pressButton();
	}
}

void MainMenuState::render()
{
	for (const auto& button : buttons)
	{
		m_window.draw(button.getSprite());
	}
	for (const auto& buttonText : buttonsTexts)
	{
		m_window.draw(buttonText);
	}
}

void MainMenuState::pressButton()
{
	if (m_onHoverButton == 0)
	{
		m_currentState = "transitionToPlaying";
	}
	else if (m_onHoverButton == 2)
	{
		m_currentState = "exiting";
	}
}
