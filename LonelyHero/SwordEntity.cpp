#include "SwordEntity.h"

SwordEntity::SwordEntity(sf::Vector2f firstPosition)
	: DamageEntity{ firstPosition }
{
	m_attackHitbox.setOrigin(sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight } / 2.f);

	m_attackHitbox.setOutlineColor(sf::Color::Red);
	m_attackHitbox.setOutlineThickness(1.f);
}

// Updates the state of m_isAttacking and also calls updateHitbox()
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
		if ((m_isAttacking && m_frameCount >= m_currentAnimationFramesAmount) || m_inDamageCooldown == true)
		{
			m_previousAttackingAnimation = m_currentTexture;
			m_isAttacking = false;
		}
	}

	updateHitbox();
}

// Called inside updateAttack()
void SwordEntity::updateHitbox()
{
	/*
	QUICK NOTE about hitbox: it is just a shape rectangle. To spawn it, I only set a size and a position relative to the entity for it. In this state, it "exists".
	When is not attacking, I just set its size to 0 and the position to negative coords so it kinda "vanishes" and "doesn't exist".
	*/

	// "spawn" the hitbox only between certain frames of the attacking sprite
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) || (m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame))
	{
		m_attackHitbox.setSize(sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight });
		m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
	}
	else
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
}

// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
void SwordEntity::updateTexture()
{
	if (m_entityName == "player")
	{
		if (m_dying)
		{
			changeCurrentTexture(constants::knightDeathAnimationFramesAmount, m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")));
		}
		else if (m_hitted)
		{
			changeCurrentTexture(constants::knightHitAnimationFramesAmount, m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")));
		}
		else if (m_velocity.y != 0.f && !m_canJump)
		{
			m_velocity.y > 0.f ? changeCurrentTexture(constants::knightFallingAnimationFramesAmount, m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling"))) : changeCurrentTexture(constants::knightJumpingAnimationFramesAmount, m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")));;
		}
		else if (!m_isAttacking)
		{
			m_isRunning ? changeCurrentTexture(constants::knightRunningAnimationFramesAmount, m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running"))) : changeCurrentTexture(constants::knightIdleAnimationFramesAmount, m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")));
		}
		else if (m_isAttacking)
		{
			m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2"))) : changeCurrentTexture(constants::knightAttackingAnimationFramesAmount, m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")));
		}
	}
	else if (m_entityName == "enemy")
	{
		if (m_dying)
		{
			changeCurrentTexture(constants::knightDeathAnimationFramesAmount, m_texturesActionName.at("Death"), m_texturesNamePath.at(m_texturesActionName.at("Death")));
		}
		else if (m_hitted)
		{
			changeCurrentTexture(constants::knightHitAnimationFramesAmount, m_texturesActionName.at("Hitted"), m_texturesNamePath.at(m_texturesActionName.at("Hitted")));
		}
		else if (m_velocity.y != 0.f && !m_canJump)
		{
			m_velocity.y > 0.f ? changeCurrentTexture(constants::knightFallingAnimationFramesAmount, m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling"))) : changeCurrentTexture(constants::knightJumpingAnimationFramesAmount, m_texturesActionName.at("Jumping"), m_texturesNamePath.at(m_texturesActionName.at("Jumping")));;
		}
		else if (!m_isAttacking)
		{
			m_isRunning ? changeCurrentTexture(constants::knightRunningAnimationFramesAmount, m_texturesActionName.at("Running"), m_texturesNamePath.at(m_texturesActionName.at("Running"))) : changeCurrentTexture(constants::knightIdleAnimationFramesAmount, m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle")));
		}
		else if (m_isAttacking)
		{
			m_previousAttackingAnimation == m_entityName + "Attacking1" ? changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, m_texturesActionName.at("Attacking2"), m_texturesNamePath.at(m_texturesActionName.at("Attacking2"))) : changeCurrentTexture(constants::knightAttackingAnimationFramesAmount, m_texturesActionName.at("Attacking1"), m_texturesNamePath.at(m_texturesActionName.at("Attacking1")));
		}
	}
	
}

// Sets m_dead to true and "zeroes" some attributes
void SwordEntity::die()
{
	m_dead = true;
	m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
	m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}
