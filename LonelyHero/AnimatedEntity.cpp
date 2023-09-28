#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(int spriteWidth, int spriteHeight, int animationFramesAmount, float spriteScale)
	: DrawableEntity{spriteWidth, spriteHeight, spriteScale}
	, m_currentAnimationFramesAmount{ animationFramesAmount }
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
