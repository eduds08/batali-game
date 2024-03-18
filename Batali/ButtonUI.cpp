#include "ButtonUI.h"

ButtonUI::ButtonUI(sf::Vector2f position, const std::string& stateRelated, const std::string& buttonTextString, const sf::Font* font)
	: UI{}
{
	init(position, stateRelated, buttonTextString, font);
}

void ButtonUI::init(sf::Vector2f position, const std::string& stateRelated, const std::string& buttonTextString, const sf::Font* font)
{
	m_stateRelated = stateRelated;

	setTexture("button", "./assets/ui/button.png");

	m_spriteWidth = BUTTON_WIDTH;
	m_spriteHeight = BUTTON_HEIGHT;

	// Initialize button's sprite
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });
	m_sprite.setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);
	m_sprite.setScale(5.f, 5.f);
	setSpritePosition(position);

	// Initialize button's text
	m_buttonText.setFont(*font);
	m_buttonText.setString(buttonTextString);
	m_buttonText.setOrigin(m_buttonText.getLocalBounds().width / 2.f, m_buttonText.getLocalBounds().height / 2.f);
	m_buttonText.setFillColor(sf::Color{231, 210, 124});
	m_buttonText.setPosition(getSpritePosition());
}

void ButtonUI::update(bool onHover)
{
	if (onHover)
	{
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth, 0, m_spriteWidth, m_spriteHeight });
	}
	else
	{
		m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });
	}

	m_buttonText.setPosition(onHover ? getSpritePosition() + BUTTON_TEXT_ON_HOVER_OFFSET : getSpritePosition());
}

void ButtonUI::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
	window.draw(m_buttonText);
}
