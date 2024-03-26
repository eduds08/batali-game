#include "AnimatedActor.h"

AnimatedActor::AnimatedActor()
	: SpriteActor{}
{
}

void AnimatedActor::updateAnimation()
{
	updateTexture();
	animateSprite();
}

void AnimatedActor::changeCurrentTexture(const std::string& textureName, const std::string& texturePath, bool loopAnimation)
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

void AnimatedActor::animateSprite()
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

void AnimatedActor::initTexturesMap()
{
	// QUICK NOTE: the game folder has to have a folder with the same name of m_actorName (as you can see in the code below).

	m_texturesActionName.emplace("Dying", m_actorName + "Dying");
	m_texturesActionName.emplace("Hitted", m_actorName + "Hitted");
	m_texturesActionName.emplace("Falling", m_actorName + "Falling");
	m_texturesActionName.emplace("Jumping", m_actorName + "Jumping");
	m_texturesActionName.emplace("Running", m_actorName + "Running");
	m_texturesActionName.emplace("Idle", m_actorName + "Idle");
	m_texturesActionName.emplace("Attack1", m_actorName + "Attack1");
	m_texturesActionName.emplace("Attack2", m_actorName + "Attack2");
	m_texturesActionName.emplace("Roll", m_actorName + "Roll");
	m_texturesActionName.emplace("AirAttack", m_actorName + "AirAttack");
	m_texturesActionName.emplace("Ultimate", m_actorName + "Ultimate");
	m_texturesActionName.emplace("FastHitted", m_actorName + "FastHitted");

	m_texturesNamePath.emplace(m_texturesActionName.at("Dying"), "./assets/" + m_actorName + "/_Dying.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Hitted"), "./assets/" + m_actorName + "/_Hitted.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Falling"), "./assets/" + m_actorName + "/_Falling.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Jumping"), "./assets/" + m_actorName + "/_Jumping.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Running"), "./assets/" + m_actorName + "/_Running.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Idle"), "./assets/" + m_actorName + "/_Idle.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attack1"), "./assets/" + m_actorName + "/_Attack1.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attack2"), "./assets/" + m_actorName + "/_Attack2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Roll"), "./assets/" + m_actorName + "/_Roll.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("AirAttack"), "./assets/" + m_actorName + "/_AirAttack.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Ultimate"), "./assets/" + m_actorName + "/_Ultimate.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("FastHitted"), "./assets/" + m_actorName + "/_FastHitted.png");
}
