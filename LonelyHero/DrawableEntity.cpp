#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(int spriteWidth, int spriteHeight)
	: m_texturesManager(TextureManager::getInstance())
	, m_spriteWidth{ spriteWidth }
	, m_spriteHeight{ spriteHeight }
{
}

void DrawableEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(textureName, texturePath));
}

void DrawableEntity::setSpriteSettings(sf::Vector2f position, sf::Vector2f scaleFactor)
{
	m_spriteScale = scaleFactor;
	m_sprite.setScale(m_spriteScale);
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });
	m_sprite.setPosition(position);
}
