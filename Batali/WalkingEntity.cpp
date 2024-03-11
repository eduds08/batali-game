#include "WalkingEntity.h"

WalkingEntity::WalkingEntity()
	: ColliderEntity{}
{
}

void WalkingEntity::handleCollision()
{
	// Sets y-velocity to 0 if entity collides in bottom or top
	if (m_collisionDirection.y != 0.f)
	{
		m_velocity.y = 0.f;
	}

	// Sets knockbackVelocity to 0 if entity is pushed against a wall after being attacked
	if (m_isCollidingHorizontally)
	{
		setKnockbackVelocity(0.f);
	}

	// Sets canJump to true if entity collides in bottom
	m_canJump = m_collisionDirection.y > 0.f;
}

void WalkingEntity::updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime, bool conditionRoll)
{
	if (m_stamina == 100)
	{
		m_staminaRecoverClock.restart();
	}

	m_velocity.x = 0.f;
	m_isRunning = true;

	// Only runs when not on roll
	if (conditionRunLeft && !m_onRoll && getAttackMode() != "onUltimate" && !getOnWindHashashinUltimate())
	{
		m_facingRight = -1;
		m_velocity.x -= m_speed;
	}
	else if (conditionRunRight && !m_onRoll && getAttackMode() != "onUltimate" && !getOnWindHashashinUltimate())
	{
		m_facingRight = 1;
		m_velocity.x += m_speed;
	}
	else
	{
		m_isRunning = false;
	}

	// Only can roll when on ground and not on Hitted animation
	if (conditionRoll && m_canJump && !getHitted() && !m_onRoll && m_stamina > 0 && m_currentTexture != m_entityName + "Roll" && getAttackMode() == "off" && !getOnWindHashashinUltimate())
	{
		m_stamina -= 50;
		m_onRoll = true;
	}

	if (m_onRoll)
	{
		m_velocity.x += (m_facingRight * m_speed);
	}

	// End onRoll animation
	if (m_onRoll && m_animationEnd && m_currentTexture == m_entityName + "Roll")
	{
		m_onRoll = false;
	}

	flipSprite();

	if (conditionJump && m_canJump && getAttackMode() == "off" && !m_onRoll && !getOnWindHashashinUltimate())
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * GRAVITY * m_jumpHeight);
	}

	m_velocity.y += GRAVITY * deltaTime;

	// If m_hitted is true (hitted sprite set), sets x-velocity to 0 so it can't move
	if (getHitted())
	{
		m_velocity.x = 0.f;
	}

	m_staminaRecoverTime = m_staminaRecoverClock.getElapsedTime().asSeconds();
	if (m_staminaRecoverTime > 2.f)
	{
		if (m_stamina < 100)
		{
			m_stamina += 50;
		}
		m_staminaRecoverClock.restart();
	}
}
