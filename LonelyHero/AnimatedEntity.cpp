#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(int spriteWidth, int spriteHeight, int animationFramesAmount, float animationSwitchTime)
	: DrawableEntity{spriteWidth, spriteHeight}
	, m_currentAnimationFramesAmount{ animationFramesAmount }
	, m_animationSwitchTime{ animationSwitchTime }
{
}

void AnimatedEntity::setSpriteTexture(const std::string& textureName, const std::string& texturePath)
{
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(textureName, texturePath));
	m_currentTexture = textureName;
	m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
}

void AnimatedEntity::updateAnimation()
{
	AnimationManager::animateSprite(m_sprite, m_currentAnimationFramesAmount, m_spriteWidth, m_spriteHeight, m_frameCount);
}
