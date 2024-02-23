#include "CharacterPortraitUI.h"

CharacterPortraitUI::CharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, float spriteScale)
	: UI{ textureName, texturePath, position }
{
	m_spriteWidth = constants::characterPortraitSpriteWidth;
	m_spriteHeight = constants::characterPortraitSpriteHeight;

	m_sprite.setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);

	m_sprite.setScale(spriteScale, spriteScale);

	m_portraitBorder = sf::RectangleShape{sf::Vector2f{m_spriteWidth * spriteScale, m_spriteHeight * spriteScale}};

	m_portraitBorder.setOutlineThickness(1.f);
	m_portraitBorder.setOutlineColor(sf::Color::Red);

	m_portraitBorder.setOrigin(m_portraitBorder.getSize() / 2.f);
	m_portraitBorder.setPosition(m_sprite.getPosition());

	m_portraitBorder.setFillColor(sf::Color::Transparent);
}

void CharacterPortraitUI::update(bool onHover)
{
	if (onHover)
	{
		m_portraitBorder.setOutlineColor(sf::Color::Green);
	}
	else
	{
		m_portraitBorder.setOutlineColor(sf::Color::Red);
	}
}
