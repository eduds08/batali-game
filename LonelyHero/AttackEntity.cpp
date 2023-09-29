#include "AttackEntity.h"

AttackEntity::AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: MovableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
}

void AttackEntity::updateAttack(const std::string& entity)
{
	if (m_isAttacking)
	{
		m_velocity.x = 0.f;
	}

	if ((m_currentTexture == entity + "Attacking2" && m_frameCount >= 5) || (m_currentTexture == entity + "Attacking1" && m_frameCount >= 3))
	{
		m_previousAttackingAnimation = m_currentTexture;
		m_isAttacking = false;
	}
}

void AttackEntity::updateHitbox()
{
	if (m_isAttacking)
	{
		if (!m_hitbox)
		{
			m_hitbox = new SwordHitbox();
		}
	}
	else
	{
		if (m_hitbox)
		{
			delete m_hitbox;
			m_hitbox = nullptr;
		}
	}

	if (m_hitbox)
	{
		m_hitbox->setPosition( getPosition() + sf::Vector2f(getSize().x * m_facingRight, 0.f));
	}
}
