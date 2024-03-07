#include "BigCharacterPortraitUI.h"

BigCharacterPortraitUI::BigCharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Color borderColor)
	: CharacterPortraitUI{}
{
	setTexture(textureName, texturePath);

	float spriteScale = 5.f;

	m_spriteWidth = CHARACTER_PORTRAIT_WIDTH;
	m_spriteHeight = CHARACTER_PORTRAIT_HEIGHT;

	setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);

	setScale(spriteScale);

	setSpritePosition(position);

	m_portraitBorder = sf::RectangleShape{ sf::Vector2f{m_spriteWidth* spriteScale, m_spriteHeight* spriteScale} };

	m_portraitBorder.setOutlineThickness(1.f);
	m_portraitBorder.setOutlineColor(borderColor);

	m_portraitBorder.setOrigin(m_portraitBorder.getSize() / 2.f);

	m_portraitBorder.setPosition(m_sprite.getPosition());
	m_portraitBorder.setFillColor(sf::Color::Black);
}