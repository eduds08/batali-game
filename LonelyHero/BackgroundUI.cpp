#include "BackgroundUI.h"

BackgroundUI::BackgroundUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i spriteSize, float scale)
	: UI{ textureName, texturePath, position }
{
	m_spriteWidth = spriteSize.x;
	m_spriteHeight = spriteSize.y;

	m_sprite.setOrigin(m_spriteWidth / 2.f, m_spriteHeight / 2.f);

	m_sprite.setScale(scale, scale);

	m_sprite.setPosition(position);
}
