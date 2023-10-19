#include "MovableEntity.h"

MovableEntity::MovableEntity(sf::Vector2f firstPosition)
	: AnimatedEntity{}
	, ColliderEntity{ firstPosition }
{
}

// Called if isCollidingWith() return true.
void MovableEntity::handleCollision()
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

// Move the shape and update the sprite position to the same place
void MovableEntity::move(float& deltaTime)
{
	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x, getPosition().y - (m_spriteHeight - getSize().y) / 2.f});
}

// Updates velocity components of the entity
void MovableEntity::updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime)
{
	m_velocity.x = 0.f;
	m_isRunning = true;

	if (conditionRunLeft)
	{
		m_facingRight = -1;
		m_velocity.x -= m_speed;
	}
	else if (conditionRunRight)
	{
		m_facingRight = 1;
		m_velocity.x += m_speed;
	}
	else
	{
		m_isRunning = false;
	}

	flipSprite();

	if (conditionJump && m_canJump && !getIsAttacking())
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * constants::gravity * constants::playerJumpSpeed);
	}

	m_velocity.y += constants::gravity * deltaTime;

	// If entity was attacked and it is still in damageCooldown, sets x-velocity to 0 so it can't move
	if (getInDamageCooldown())
	{
		m_velocity.x = 0.f;
	}
}
