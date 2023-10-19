#include "MovableEntity.h"

MovableEntity::MovableEntity(sf::Vector2f firstPosition)
	: AnimatedEntity{}
	, ColliderEntity{ firstPosition }
{
}

// Called if isCollidingWith() return true
void MovableEntity::handleCollision()
{
	if (m_collisionDirection.y != 0.f)
	{
		m_velocity.y = 0.f;
	}
}

// Move the shape and update the sprite position to the same place
void MovableEntity::move(float& deltaTime)
{
	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x, getPosition().y - (m_spriteHeight - getSize().y) / 2.f});
}

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

	if (getInDamageCooldown())
	{
		m_velocity.x = 0.f;
	}
}
