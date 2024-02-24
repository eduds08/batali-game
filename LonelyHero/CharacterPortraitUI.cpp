#include "CharacterPortraitUI.h"

CharacterPortraitUI::CharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool isBig)
	: UI{ textureName, texturePath, position }
	, m_isBig{isBig}
{
	m_spriteWidth = constants::characterPortraitSpriteWidth;
	m_spriteHeight = constants::characterPortraitSpriteHeight;

	m_sprite.setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);

	float spriteScale = isBig ? 5.f : 1.f;

	m_sprite.setScale(spriteScale, spriteScale);

	m_portraitBorder = sf::RectangleShape{sf::Vector2f{m_spriteWidth * spriteScale, m_spriteHeight * spriteScale}};

	m_portraitBorder.setOutlineThickness(isBig ? 1.f : 3.f);
	m_portraitBorder.setOrigin(m_portraitBorder.getSize() / 2.f);
	m_portraitBorder.setPosition(m_sprite.getPosition());
	m_portraitBorder.setFillColor(sf::Color::Transparent);
}

void CharacterPortraitUI::update(bool onHover, sf::Color color)
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
