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
	updateTexture();
	animateSprite();
}

void AnimatedEntity::changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath)
{
	if (m_currentTexture != textureName)
	{
		m_currentAnimationFramesAmount = animationFramesAmount;
		m_frameCount = 0;
		setSpriteTexture(textureName, texturePath);
	}
}

void AnimatedEntity::animateSprite()
{
	if (m_frameCount == m_currentAnimationFramesAmount)
		m_frameCount = 0;
	m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	++m_frameCount;
}