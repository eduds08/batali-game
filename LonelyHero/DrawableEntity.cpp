#include "DrawableEntity.h"
#include "Game.h"

DrawableEntity::DrawableEntity(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime)
	: m_frameWidth{ frameWidth }
	, m_frameHeight{ frameHeight }
	, m_frameAmount{ frameAmount }
	, m_switchAnimationTime{ switchAnimationTime }
{
}

void DrawableEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
	m_currentSprite = textureName;
}

void DrawableEntity::setSpriteSettings(float xCoord, float yCoord, float scaleX, float scaleY)
{
	m_sprite.setPosition(xCoord, yCoord);

	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	m_sprite.setScale(scaleX, scaleY);
}

void DrawableEntity::updateAnimation(float& deltaTime)
{
	m_totalAnimationTime += deltaTime;

	if (m_totalAnimationTime >= m_switchAnimationTime)
	{
		m_totalAnimationTime -= m_switchAnimationTime;
		AnimationManager::animateSprite(m_sprite, m_frameAmount, m_frameWidth, m_frameHeight, m_frameCount);
	}
}
