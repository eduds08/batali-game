#include "SmallCharacterPortraitUI.h"

SmallCharacterPortraitUI::SmallCharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position)
	: CharacterPortraitUI{}
{
	setTexture(textureName, texturePath);

	m_spriteWidth = CHARACTER_PORTRAIT_WIDTH;
	m_spriteHeight = CHARACTER_PORTRAIT_HEIGHT;

	setSpritePosition(position);

	m_portraitBorder = sf::RectangleShape{ sf::Vector2f{static_cast<float>(m_spriteWidth), static_cast<float>(m_spriteHeight)} };

	m_portraitBorder.setOutlineThickness(1.f);

	m_portraitBorder.setPosition(m_sprite.getPosition());
	m_portraitBorder.setFillColor(sf::Color::Black);
}

void SmallCharacterPortraitUI::update(bool onHover, sf::Color color)
{
	if (onHover)
	{
		m_portraitBorder.setOutlineColor(color);
	}
	else
	{
		m_portraitBorder.setOutlineColor(sf::Color::White);
	}
}
