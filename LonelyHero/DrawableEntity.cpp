#include "DrawableEntity.h"
#include "Game.h"

DrawableEntity::DrawableEntity(int frameWidth, int frameHeight)
	: m_frameWidth{ frameWidth }
	, m_frameHeight{ frameHeight }
{
}

void DrawableEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
}

void DrawableEntity::setSpriteSettings(float xCoord, float yCoord, float scaleX, float scaleY)
{
	m_sprite.setPosition(xCoord, yCoord);

	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	m_sprite.setScale(scaleX, scaleY);
}
