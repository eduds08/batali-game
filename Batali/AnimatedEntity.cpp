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
		setTexture(textureName, texturePath);
		m_currentAnimationFramesAmount = m_sprite.getTexture()->getSize().x / m_spriteWidth;
		m_currentTexture = textureName;
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
	}
}

void AnimatedEntity::animateSprite()
{
	// Sets next frame if animationEnd = false
	if (!m_animationEnd)
	{
		m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * m_frameCount, 0, m_spriteWidth, m_spriteHeight });
		++m_frameCount;
	}

	// If all frames were played, restarts the animation if loop=true or indicates that animationEnd=true otherwise
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

	m_texturesActionName.emplace("Dying", m_entityName + "Dying");
	m_texturesActionName.emplace("Hitted", m_entityName + "Hitted");
	m_texturesActionName.emplace("Falling", m_entityName + "Falling");
	m_texturesActionName.emplace("Jumping", m_entityName + "Jumping");
	m_texturesActionName.emplace("Running", m_entityName + "Running");
	m_texturesActionName.emplace("Idle", m_entityName + "Idle");
	m_texturesActionName.emplace("Attack1", m_entityName + "Attack1");
	m_texturesActionName.emplace("Attack2", m_entityName + "Attack2");
	m_texturesActionName.emplace("Roll", m_entityName + "Roll");
	m_texturesActionName.emplace("AirAttack", m_entityName + "AirAttack");
	m_texturesActionName.emplace("Ultimate", m_entityName + "Ultimate");
	m_texturesActionName.emplace("FastHit", m_entityName + "FastHit");

	m_texturesNamePath.emplace(m_texturesActionName.at("Dying"), "./assets/" + m_entityName + "/_Dying.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Hitted"), "./assets/" + m_entityName + "/_Hitted.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Falling"), "./assets/" + m_entityName + "/_Falling.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Jumping"), "./assets/" + m_entityName + "/_Jumping.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Running"), "./assets/" + m_entityName + "/_Running.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Idle"), "./assets/" + m_entityName + "/_Idle.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attack1"), "./assets/" + m_entityName + "/_Attack1.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attack2"), "./assets/" + m_entityName + "/_Attack2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Roll"), "./assets/" + m_entityName + "/_Roll.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("AirAttack"), "./assets/" + m_entityName + "/_AirAttack.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Ultimate"), "./assets/" + m_entityName + "/_Ultimate.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("FastHit"), "./assets/" + m_entityName + "/_FastHit.png");
}
