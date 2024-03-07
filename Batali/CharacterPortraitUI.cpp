#include "CharacterPortraitUI.h"

CharacterPortraitUI::CharacterPortraitUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool isBig, sf::Color borderColor)
	: UI{}
{
	init(textureName, texturePath, position, isBig, borderColor);
}

void CharacterPortraitUI::init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, bool isBig, sf::Color borderColor)
{
	setTexture(textureName, texturePath);

	m_spriteWidth = CHARACTER_PORTRAIT_WIDTH;
	m_spriteHeight = CHARACTER_PORTRAIT_HEIGHT;

	if (isBig)
		setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);

	float spriteScale = isBig ? 5.f : 1.f;

	setScale(spriteScale);

	setSpritePosition(position);

	m_portraitBorder = sf::RectangleShape{ sf::Vector2f{m_spriteWidth* spriteScale, m_spriteHeight* spriteScale} };

	m_portraitBorder.setOutlineThickness(1.f);
	m_portraitBorder.setOutlineColor(borderColor);

	if (isBig)
		m_portraitBorder.setOrigin(m_portraitBorder.getSize() / 2.f);

	m_portraitBorder.setPosition(m_sprite.getPosition());
	m_portraitBorder.setFillColor(sf::Color::Black);
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