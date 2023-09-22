#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime)
	: DrawableEntity{spriteWidth, spriteHeight, shapeWidth, shapeHeight}
	, m_animationFramesAmount{ animationFramesAmount }
	, m_animationSwitchTime{ animationSwitchTime }
{
}

void AnimatedEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
	m_currentSprite = textureName;
}

void AnimatedEntity::updateAnimation(float& deltaTime)
{
	m_animationTotalTime += deltaTime;

	if (m_animationTotalTime >= m_animationSwitchTime)
	{
		m_animationTotalTime -= m_animationSwitchTime;
		AnimationManager::animateSprite(m_sprite, m_animationFramesAmount, m_spriteWidth, m_spriteHeight, m_frameCount);
	}
}
