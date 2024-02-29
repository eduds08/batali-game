#include "ButtonAuxState.h"

ButtonAuxState::ButtonAuxState(sf::RenderWindow& window)
	: StateContext{ window }
{
}

void ButtonAuxState::initButton(const std::string& text, sf::Vector2f position, const std::string& stateRelated)
{
	m_buttons.emplace_back(ButtonUI{ "button", "./assets/ui/button.png", position, stateRelated });

	sf::Text buttonText{ text, m_font };
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.f, buttonText.getLocalBounds().height / 2.f);
	buttonText.setFillColor(sf::Color{231, 210, 124});
	buttonText.setPosition(m_buttons.back().getPosition());

	m_buttonsTexts.emplace_back(buttonText);
}

void ButtonAuxState::updateButtons(bool isUpDown)
{
	sf::Keyboard::Scancode aheadKey = sf::Keyboard::Scancode::Down;
	sf::Keyboard::Scancode backKey = sf::Keyboard::Scancode::Up;

	if (!isUpDown)
	{
		aheadKey = sf::Keyboard::Scancode::Right;
		backKey = sf::Keyboard::Scancode::Left;
	}

	// Move ahead
	if (m_pressedKey == aheadKey)
	{
		if (m_onHoverButton < m_buttons.size() - 1)
		{
			++m_onHoverButton;
		}
	}
	// Move back
	else if (m_pressedKey == backKey)
	{
		if (m_onHoverButton > 0)
		{
			--m_onHoverButton;
		}
	}

	// Upate the visual design of the buttons (according to its state -> onHover OR not onHover)
	for (size_t i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].update(i == m_onHoverButton);
		m_buttonsTexts[i].setPosition(m_buttons[i].getPosition());

		if (i == m_onHoverButton)
		{
			m_buttonsTexts[i].setPosition(m_buttons[i].getPosition() + sf::Vector2f{ 0.f, 2.f });
		}
	}

	// Button pressed
	if (m_pressedKey == sf::Keyboard::Scancode::Enter)
	{
		pressButton(m_buttons[m_onHoverButton]);
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void ButtonAuxState::renderButtons()
{
	for (const auto& button : m_buttons)
	{
		m_window.draw(button.getSprite());
	}
	for (const auto& buttonText : m_buttonsTexts)
	{
		m_window.draw(buttonText);
	}
}

void ButtonAuxState::pressButton(ButtonUI buttonPressed)
{
	m_currentState = buttonPressed.getStateRelated();
}
