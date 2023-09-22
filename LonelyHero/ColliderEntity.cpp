#include "ColliderEntity.h"

bool ColliderEntity::isColliding(sf::RectangleShape& shape)
{
	float groundHalfSizeX = shape.getSize().x / 2.f;
	float groundHalfSizeY = shape.getSize().y / 2.f;
	float groundPositionX = shape.getPosition().x;
	float groundPositionY = shape.getPosition().y;

	float playerHalfSizeX = getSize().x / 2.f;
	float playerHalfSizeY = getSize().y / 2.f;
	float playerPositionX = getPosition().x;
	float playerPositionY = getPosition().y;

	float deltaX = groundPositionX - playerPositionX;
	float deltaY = groundPositionY - playerPositionY;

	float intersectX = abs(deltaX) - (groundHalfSizeX + playerHalfSizeX);
	float intersectY = abs(deltaY) - (groundHalfSizeY + playerHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		if (intersectX > intersectY) {

			if (deltaX > 0.f)
			{
				walk(intersectX, 0.f);
				m_collisionDirection.x = 1.0f;
			}
			else
			{
				walk(-intersectX, 0.f);
				m_collisionDirection.x = -1.0f;
			}
			m_collisionDirection.y = 0.f;
		}
		else
		{
			if (deltaY > 0.f)
			{
				walk(0.f, intersectY);
				m_collisionDirection.y = 1.0f;
			}
			else
			{
				walk(0.f, -intersectY);
				m_collisionDirection.y = -1.0f;
			}
			m_collisionDirection.x = 0.f;
		}

		return true;
	}

	return false;
}

//void ColliderEntity::onCollision(sf::Vector2f& velocity)
//{
//	if (m_collisionDirection.x != 0.f)
//	{
//		velocity.x = 0.f;
//	}
//	if (m_collisionDirection.y != 0.f)
//	{
//		velocity.y = 0.f;
//		
//	}
//}

void ColliderEntity::onCollision(float& velocityX, float& velocityY)
{
	if (m_collisionDirection.x != 0.f)
	{
		velocityX = 0.f;
	}
	if (m_collisionDirection.y != 0.f)
	{
		velocityY = 0.f;

	}
}