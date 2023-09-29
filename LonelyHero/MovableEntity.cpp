#include "MovableEntity.h"

MovableEntity::MovableEntity(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, float spriteScale)
	: AnimatedEntity{spriteWidth, spriteHeight, animationFramesAmount, spriteScale}
	, ColliderEntity{shapeWidth, shapeHeight, firstPosition}
{
}

void MovableEntity::handleCollision()
{
	if (m_collisionDirection.x != 0.f)
	{
		m_velocity.x = 0.f;
	}
	if (m_collisionDirection.y != 0.f)
	{
		m_velocity.y = 0.f;
		
	}
}

void MovableEntity::move(float yAxisAdjustment, float& deltaTime)
{
	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f - yAxisAdjustment});
}
