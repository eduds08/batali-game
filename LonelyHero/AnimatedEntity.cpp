#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount)
	: DrawableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath }
	, m_currentAnimationFramesAmount{ animationFramesAmount }
{
	m_currentTexture = textureName;
	m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth* m_frameCount, 0, m_spriteWidth, m_spriteHeight });
}

// inside animation Thread
void AnimatedEntity::updateAnimation()
{
	updateTexture();
	animateSprite();
}

/*
Called when the object changes its animation. Eg.: from running animation to jumping.
*/
void AnimatedEntity::changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath)
{
	if (m_currentTexture != textureName)
	{
		m_currentAnimationFramesAmount = animationFramesAmount;
		m_frameCount = 0;
		m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(textureName, texturePath));
		m_currentTexture = textureName;
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth* m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	}
}

// Update each frame of the animation texture
void AnimatedEntity::animateSprite()
{
	if (m_frameCount == m_currentAnimationFramesAmount)
		m_frameCount = 0;
	m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth* m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	++m_frameCount;
}