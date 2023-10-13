#include "MovableEntity.h"
#include "AttackEntity.h"

MovableEntity::MovableEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: AnimatedEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount }
	, ColliderEntity{ shapeWidth, shapeHeight, firstPosition }
{
}

// Set velocity to 0 according to the collision direction
void MovableEntity::handleCollision()
{	
	
	if (m_collisionDirection.x != 0.f)
	{
		m_velocity.x = 0.f;
		knockbackVelocity = 0.f;
	}
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

void MovableEntity::knockbackMove(float& deltaTime)
{
	m_shape.move(sf::Vector2f{knockbackVelocity * -1.f * m_facingRight, 0.f} * deltaTime);
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
