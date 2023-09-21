#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime)
	: DrawableEntity{frameWidth, frameHeight}
	, m_frameAmount{ frameAmount }
	, m_switchAnimationTime{ switchAnimationTime }
{
}

void AnimatedEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
	m_currentSprite = textureName;
}

void AnimatedEntity::updateAnimation(float& deltaTime)
{
	m_totalAnimationTime += deltaTime;

	if (m_totalAnimationTime >= m_switchAnimationTime)
	{
		m_totalAnimationTime -= m_switchAnimationTime;
		AnimationManager::animateSprite(m_sprite, m_frameAmount, m_frameWidth, m_frameHeight, m_frameCount);
	}
}
