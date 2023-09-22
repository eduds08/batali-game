#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight)
	: m_spriteWidth{ spriteWidth }
	, m_spriteHeight{ spriteHeight }
	, m_shapeWidth{ shapeWidth }
	, m_shapeHeight{ shapeHeight }
{
}

void DrawableEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
}

void DrawableEntity::setShapeSettings(sf::Vector2f position)
{
	m_shape.setSize(sf::Vector2f{ m_shapeWidth, m_shapeHeight });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(position.x, position.y);

	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);
}

void DrawableEntity::setSpriteSettings()
{
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });
	m_sprite.setPosition(m_shape.getPosition());
}
