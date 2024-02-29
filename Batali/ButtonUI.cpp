#include "ButtonUI.h"

ButtonUI::ButtonUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, const std::string& stateRelated)
	: UI{}
{
	init(textureName, texturePath, position, stateRelated);
}

void ButtonUI::init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, const std::string& stateRelated)
{
	m_stateRelated = stateRelated;

	setTexture(textureName, texturePath);

	m_spriteWidth = constants::buttonSpriteWidth;
	m_spriteHeight = constants::buttonSpriteHeight;

	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });

	setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);

	setScale(5.f);

	setPosition(position);
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
}