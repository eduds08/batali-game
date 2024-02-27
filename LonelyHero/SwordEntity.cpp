#include "SwordEntity.h"

SwordEntity::SwordEntity(sf::Vector2f firstPosition)
	: DamageEntity{ firstPosition }
{
}

void SwordEntity::updateAttack(bool attackCondition)
{
	if (attackCondition && m_canJump && !m_isAttacking && !m_onRoll)
	{
		m_isAttacking = true;
		m_isAirAttacking = false;
	}
	else if (attackCondition && !m_canJump && !m_isAttacking && !m_onRoll)
	{
		m_isAttacking = true;
		m_isAirAttacking = true;
	}

	if (m_isAttacking)
	{
		if (!m_isAirAttacking)
		{
			// Don't let the entity move if it is attacking on ground
			m_velocity.x = 0.f;
			m_velocity.y = 0.f;

			// Stop the attack when attack animation ends (and also stores the current animation as the previous one so the next attack uses the other attacking animation) or when entity gets hitted
			if (((m_currentTexture == m_entityName + "Attacking1" || m_currentTexture == m_entityName + "Attacking2") && m_animationEnd) || m_inDamageCooldown == true)
			{
				if (m_inDamageCooldown == false)
				{
					m_previousAttackingAnimation = m_currentTexture;
				}
				m_isAttacking = false;
			}
		}
		else
		{
			m_velocity.x = 0.f;

			if ((m_currentTexture == m_entityName + "AirAttacking" && m_animationEnd) || m_inDamageCooldown == true || (m_canJump && m_currentTexture == m_entityName + "Falling"))
			{
				m_isAttacking = false;
				m_isAirAttacking = false;
			}
		}
	}

	updateHitbox();
}

void SwordEntity::die()
{
	m_dead = true;
	m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
	m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}
