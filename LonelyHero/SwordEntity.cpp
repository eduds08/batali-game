#include "SwordEntity.h"

SwordEntity::SwordEntity(sf::Vector2f firstPosition)
	: DamageEntity{ firstPosition }
{
}

void SwordEntity::updateAttack(bool attackCondition)
{
	if (attackCondition && m_canJump && !m_isAttacking)
	{
		m_isAttacking = true;
		m_isAirAttacking = false;
	}
	else if (attackCondition && !m_canJump && !m_isAttacking) 
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

			if ((m_currentTexture == m_entityName + "AirAttacking" && m_animationEnd) || m_inDamageCooldown == true)
			{
				m_isAttacking = false;
				m_isAirAttacking = false;
			}
		}
	}

	updateHitbox();
}

void SwordEntity::updateHitbox()
{
	/*
	QUICK NOTE about hitbox: it is just a shape rectangle. To spawn it, I only set a size and a position relative to the entity for it. In this state, it "exists".
	When is not attacking, I just set its size to 0 and the position to negative coords so it kinda "vanishes" and "doesn't exist".
	*/

	// "spawn" the hitbox only between certain frames of the attacking sprite
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) || 
		(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame))
	{
		m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
		m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
	}
	else
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
}

void SwordEntity::updateTexture()
{
	if (m_entityName == "enemy")
	{
		if (m_dying)
		{
			changeCurrentTexture(m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")), false);
		}
		else if (m_hitted)
		{
			changeCurrentTexture(m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")), false);
		}
		else if (m_velocity.y != 0.f && !m_canJump)
		{
			m_velocity.y > 0.f ? changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true) : changeCurrentTexture(m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")), true);;
		}
		else if (!m_isAttacking)
		{
			if (m_onRoll)
			{
				changeCurrentTexture(m_texturesActionName.at("Roll"), m_texturesNamePath.at(m_texturesActionName.at("Roll")), false);
			}
			else 
			{
				m_isRunning ? changeCurrentTexture(m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running")), true) : changeCurrentTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")), true);
			}
		}
		else if (m_isAttacking)
		{
			m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2")), false) : changeCurrentTexture(m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")), false);
		}
	}
	else if (m_entityName == "player")
	{
		if (m_dying)
		{
			changeCurrentTexture(m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")), false);
		}
		else if (m_hitted)
		{
			changeCurrentTexture(m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")), false);
		}
		else if (m_velocity.y != 0.f && !m_canJump)
		{
			if (m_isAirAttacking)
			{
				changeCurrentTexture(m_texturesActionName.at("AirAttacking"), m_texturesNamePath.at(m_texturesActionName.at("AirAttacking")), false);
			}
			else
			{
				m_velocity.y > 0.f ? changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true) : changeCurrentTexture(m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")), true);;
			}
		}
		else if (!m_isAttacking)
		{
			if (m_onRoll)
			{
				changeCurrentTexture(m_texturesActionName.at("Roll"), m_texturesNamePath.at(m_texturesActionName.at("Roll")), false);
			}
			else
			{
				m_isRunning ? changeCurrentTexture(m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running")), true) : changeCurrentTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")), true);
			}
		}
		else if (m_isAttacking)
		{
			if (!m_isAirAttacking)
			{
				m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2")), false) : changeCurrentTexture(m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")), false);
			}
		}
	}
	
}

void SwordEntity::die()
{
	m_dead = true;
	m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
	m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}
