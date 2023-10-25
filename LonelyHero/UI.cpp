#include "UI.h"

UI::UI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
	: DrawableEntity{}
{
	m_spriteWidth = 48;
	m_spriteHeight = 16;
	m_spriteScale = 2.f;

	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(textureName, texturePath));

	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });

	m_sprite.setScale(m_spriteScale, m_spriteScale);

	m_sprite.setPosition(position);
}

void UI::setRectTemp(int x)
{
	m_sprite.setTextureRect(sf::IntRect{ 0 + x, 0, m_spriteWidth, m_spriteHeight });
}
