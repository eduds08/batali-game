#include "MovableEntity.h"

MovableEntity::MovableEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: AnimatedEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, entityName }
	, ColliderEntity{ shapeWidth, shapeHeight, firstPosition }
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
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f - (m_spriteHeight - m_shape.getSize().y)});
}

void MovableEntity::updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime)
{
	m_velocity.x = 0.f;
	m_isRunning = true;

	if (conditionRunLeft)
	{
		m_facingRight = -1;
		m_velocity.x -= constants::playerSpeed;
	}
	else if (conditionRunRight)
	{
		m_facingRight = 1;
		m_velocity.x += constants::playerSpeed;
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

	if (getJustHitted())
	{
		m_velocity.x = 0.f;
	}
}
