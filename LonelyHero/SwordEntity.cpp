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
	}

	if (m_isAttacking)
	{
		// Don't let the entity move if it is attacking
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;

		// Stop the attack when attack animation ends (and also stores the current animation as the previous one so the next attack uses the other attacking animation) or when entity gets hitted
		if (((m_currentTexture == m_entityName + "Attacking1" || m_currentTexture == m_entityName + "Attacking2") && m_frameCount >= m_currentAnimationFramesAmount) || m_inDamageCooldown == true)
		{
			if (m_inDamageCooldown == false)
			{
				m_previousAttackingAnimation = m_currentTexture;
			}
			m_isAttacking = false;
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
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) || (m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame))
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
			changeCurrentTexture(constants::windHashashinDeathAnimationFramesAmount, m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")));
		}
		else if (m_hitted)
		{
			changeCurrentTexture(constants::windHashashinHitAnimationFramesAmount, m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")));
		}
		else if (m_velocity.y != 0.f && !m_canJump)
		{
			m_velocity.y > 0.f ? changeCurrentTexture(constants::windHashashinFallingAnimationFramesAmount, m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling"))) : changeCurrentTexture(constants::windHashashinJumpingAnimationFramesAmount, m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")));;
		}
		else if (!m_isAttacking)
		{
			m_isRunning ? changeCurrentTexture(constants::windHashashinRunningAnimationFramesAmount, m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running"))) : changeCurrentTexture(constants::windHashashinIdleAnimationFramesAmount, m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")));
		}
		else if (m_isAttacking)
		{
			m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(constants::windHashashinAttacking2AnimationFramesAmount, m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2"))) : changeCurrentTexture(constants::windHashashinAttackingAnimationFramesAmount, m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")));
		}
	}
	else if (m_entityName == "player")
	{
		if (m_dying)
		{
			changeCurrentTexture(constants::fireKnightDeathAnimationFramesAmount, m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")));
		}
		else if (m_hitted)
		{
			changeCurrentTexture(constants::fireKnightHitAnimationFramesAmount, m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")));
		}
		else if (m_velocity.y != 0.f && !m_canJump)
		{
			m_velocity.y > 0.f ? changeCurrentTexture(constants::fireKnightFallingAnimationFramesAmount, m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling"))) : changeCurrentTexture(constants::fireKnightJumpingAnimationFramesAmount, m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")));;
		}
		else if (!m_isAttacking)
		{
			m_isRunning ? changeCurrentTexture(constants::fireKnightRunningAnimationFramesAmount, m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running"))) : changeCurrentTexture(constants::fireKnightIdleAnimationFramesAmount, m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")));
		}
		else if (m_isAttacking)
		{
			m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(constants::fireKnightAttacking2AnimationFramesAmount, m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2"))) : changeCurrentTexture(constants::fireKnightAttackingAnimationFramesAmount, m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")));
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
