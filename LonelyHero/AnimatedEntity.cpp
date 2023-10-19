#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity()
	: DrawableEntity{}
{
}

// inside animationThread
void AnimatedEntity::updateAnimation()
{
	updateTexture();
	animateSprite();
}

// Called when the object changes its animation. Eg.: from running animation to jumping.
void AnimatedEntity::changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath)
{
	if (m_currentTexture != textureName)
	{
		m_currentAnimationFramesAmount = animationFramesAmount;
		m_frameCount = 0;
		m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(textureName, texturePath));
		m_currentTexture = textureName;
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	}
}

// Update each frame of the animation texture
void AnimatedEntity::animateSprite()
{
	if (m_frameCount == m_currentAnimationFramesAmount)
		m_frameCount = 0;
	m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	++m_frameCount;
}

void AnimatedEntity::initTexturesMap()
{
	m_texturesActionName.emplace("Death", m_entityName + "Death");
	m_texturesActionName.emplace("Hitted", m_entityName + "Hitted");
	m_texturesActionName.emplace("Falling", m_entityName + "Falling");
	m_texturesActionName.emplace("Jumping", m_entityName + "Jumping");
	m_texturesActionName.emplace("Running", m_entityName + "Running");
	m_texturesActionName.emplace("Idle", m_entityName + "Idle");
	m_texturesActionName.emplace("Attacking1", m_entityName + "Attacking1");
	m_texturesActionName.emplace("Attacking2", m_entityName + "Attacking2");

	m_texturesNamePath.emplace(m_texturesActionName.at("Death"), "./assets/" + m_entityName + "/_Death.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Hitted"), "./assets/" + m_entityName + "/_Hit.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Falling"), "./assets/" + m_entityName + "/_Fall.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Jumping"), "./assets/" + m_entityName + "/_Jump.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Running"), "./assets/" + m_entityName + "/_Run.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Idle"), "./assets/" + m_entityName + "/_Idle.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking1"), "./assets/" + m_entityName + "/_Attack1.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking2"), "./assets/" + m_entityName + "/_Attack2.png");
}
