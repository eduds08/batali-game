#include "SwordEntity.h"

SwordEntity::SwordEntity()
	: DamageEntity{}
{
}

void SwordEntity::updateAttack(bool attackCondition1, bool attackCondition2, bool ultimateCondition)
{
	if (attackCondition1 && m_canJump && !m_isAttacking && !m_onRoll && !ultimateCondition)
	{
		m_isAttacking = true;
		m_onAirAttack = false;
		m_onUltimate = false;
		m_onAttack1 = true;
		m_onAttack2 = false;
	}
	else if (attackCondition2 && m_canJump && !m_isAttacking && !m_onRoll && !ultimateCondition)
	{
		m_isAttacking = true;
		m_onAirAttack = false;
		m_onUltimate = false;
		m_onAttack1 = false;
		m_onAttack2 = true;
	}
	else if ((attackCondition1 || attackCondition2) && !m_canJump && !m_isAttacking && !m_onRoll && !ultimateCondition)
	{
		m_isAttacking = true;
		m_onAirAttack = true;
		m_onUltimate = false;
		m_onAttack1 = false;
		m_onAttack2 = false;
	}
	else if (ultimateCondition && m_canJump && !m_isAttacking && !m_onRoll && m_remainingManaToUltimate <= 0)
	{
		m_onUltimate = true;
		m_isAttacking = true;
		m_onAirAttack = false;
		m_onAttack1 = false;
		m_onAttack2 = false;

		m_remainingManaToUltimate = 5;
	}

	if (m_isAttacking)
	{
		if (!m_onAirAttack)
		{
			// Don't let the entity move if it is attacking on ground
			m_velocity.x = 0.f;
			m_velocity.y = 0.f;

			// Stop the attack when attack animation ends (and also stores the current animation as the previous one so the next attack uses the other attacking animation) or when entity gets hitted
			if (((m_currentTexture == m_entityName + "Attack1" || m_currentTexture == m_entityName + "Attack2" || m_currentTexture == m_entityName + "Ultimate") && m_animationEnd) || m_inDamageCooldown == true)
			{
				if (m_isBot && m_inDamageCooldown == false)
				{
					m_previousAttackingAnimation = m_currentTexture;
				}
				m_onUltimate = false;
				m_isAttacking = false;
				m_onAirAttack = false;
				m_onAttack1 = false;
				m_onAttack2 = false;
			}
		}
		else
		{
			m_velocity.x = 0.f;

			if ((m_currentTexture == m_entityName + "AirAttack" && m_animationEnd) || m_inDamageCooldown == true || (m_canJump && m_currentTexture == m_entityName + "Falling"))
			{
				m_onUltimate = false;
				m_isAttacking = false;
				m_onAirAttack = false;
				m_onAttack1 = false;
				m_onAttack2 = false;
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
