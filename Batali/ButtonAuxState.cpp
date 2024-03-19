#include "ButtonAuxState.h"

ButtonAuxState::ButtonAuxState(sf::RenderWindow& window)
	: StateContext{ window }
{
}

void ButtonAuxState::initTextButton(const std::string& text, sf::Vector2f position, const std::string& stateRelated)
{
	m_buttons.emplace_back(std::make_shared<TextButtonUI>(TextButtonUI{ position, stateRelated, text, &m_font }));
}

void ButtonAuxState::initImageButton(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
{
	m_buttons.emplace_back(std::make_shared<ImageButtonUI>(position, textureName, texturePath));
}

void ButtonAuxState::updateButtons(bool isUpDown)
{
	sf::Keyboard::Scancode aheadKey = isUpDown ? sf::Keyboard::Scancode::Down : sf::Keyboard::Scancode::Right;
	sf::Keyboard::Scancode backKey = isUpDown ? sf::Keyboard::Scancode::Up : sf::Keyboard::Scancode::Left;

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
		m_buttons[i]->update(i == m_onHoverButton);
	}

	// Button pressed
	if (m_pressedKey == sf::Keyboard::Scancode::Enter)
	{
		if (dynamic_cast<TextButtonUI*>(m_buttons[m_onHoverButton].get()) != nullptr)
		{
			pressTextButton(*dynamic_cast<TextButtonUI*>(m_buttons[m_onHoverButton].get()));
		}
		else if (dynamic_cast<ImageButtonUI*>(m_buttons[m_onHoverButton].get()) != nullptr)
		{
			pressImageButton();
		}
	}

	m_pressedKey = sf::Keyboard::Scancode::Unknown;
}

void ButtonAuxState::renderButtons()
{
	for (const auto& button : m_buttons)
	{
		button->render(m_window);
	}
}
