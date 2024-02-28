#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity()
	: DrawableEntity{}
{
}

void AnimatedEntity::updateAnimation()
{
	updateTexture();
	animateSprite();
}

void AnimatedEntity::changeCurrentTexture(const std::string& textureName, const std::string& texturePath, bool loopAnimation)
{
	// Checks if the texture isn't already set, so it doesn't set the same sprite more than once
	if (m_currentTexture != textureName)
	{
		m_loopAnimation = loopAnimation;
		m_animationEnd = false;
		m_frameCount = 0;
		m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
		m_currentAnimationFramesAmount = m_sprite.getTexture()->getSize().x / m_spriteWidth;
		m_currentTexture = textureName;
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	}
}

void AnimatedEntity::animateSprite()
{
	if (!m_animationEnd)
	{
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
		++m_frameCount;
	}
	if (m_frameCount == m_currentAnimationFramesAmount)
	{
		m_frameCount = 0;
		if (!m_loopAnimation)
		{
			m_animationEnd = true;
		}
	}
}

void AnimatedEntity::initTexturesMap()
{
	// QUICK NOTE: the game folder has to have a folder with the same name of m_entityName (as you can see in the code below).

	m_texturesActionName.emplace("Death", m_entityName + "Death");
	m_texturesActionName.emplace("Hitted", m_entityName + "Hitted");
	m_texturesActionName.emplace("Falling", m_entityName + "Falling");
	m_texturesActionName.emplace("Jumping", m_entityName + "Jumping");
	m_texturesActionName.emplace("Running", m_entityName + "Running");
	m_texturesActionName.emplace("Idle", m_entityName + "Idle");
	m_texturesActionName.emplace("Attacking1", m_entityName + "Attacking1");
	m_texturesActionName.emplace("Attacking2", m_entityName + "Attacking2");
	m_texturesActionName.emplace("Roll", m_entityName + "Roll");
	m_texturesActionName.emplace("AirAttacking", m_entityName + "AirAttacking");

	m_texturesNamePath.emplace(m_texturesActionName.at("Death"), "./assets/" + m_entityName + "/_Death.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Hitted"), "./assets/" + m_entityName + "/_Hit.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Falling"), "./assets/" + m_entityName + "/_Fall.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Jumping"), "./assets/" + m_entityName + "/_Jump.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Running"), "./assets/" + m_entityName + "/_Run.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Idle"), "./assets/" + m_entityName + "/_Idle.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking1"), "./assets/" + m_entityName + "/_Attack1.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking2"), "./assets/" + m_entityName + "/_Attack2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Roll"), "./assets/" + m_entityName + "/_Roll.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("AirAttacking"), "./assets/" + m_entityName + "/_AirAttack.png");
}
