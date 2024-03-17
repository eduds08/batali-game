#include "ColliderEntity.h"

ColliderEntity::ColliderEntity()
	: MovableEntity{}
{
}

bool ColliderEntity::isCollidingWith(const sf::Sprite& other)
{
	float otherHalfSizeX = other.getTexture()->getSize().x / 2.f;
	float otherHalfSizeY = other.getTexture()->getSize().y / 2.f;
	float otherPositionX = other.getPosition().x;
	float otherPositionY = other.getPosition().y;

	float thisHalfSizeX = getShapeSize().x / 2.f;
	float thisHalfSizeY = getShapeSize().y / 2.f;
	float thisPositionX = getShapePosition().x;
	float thisPositionY = getShapePosition().y;

	float deltaX = otherPositionX - thisPositionX;
	float deltaY = otherPositionY - thisPositionY;

	float intersectX = abs(deltaX) - (otherHalfSizeX + thisHalfSizeX);
	float intersectY = abs(deltaY) - (otherHalfSizeY + thisHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		if (intersectX > intersectY) {

			if (deltaX > 0.f)
			{
				m_shape.move(sf::Vector2f{ intersectX, 0.f });
				m_collisionDirection.x = 1.0f;
			}
			else
			{
				m_shape.move(sf::Vector2f{ -intersectX, 0.f });
				m_collisionDirection.x = -1.0f;
			}
			m_isCollidingHorizontally = true;
			m_collisionDirection.y = 0.f;
		}
		else
		{
			if (deltaY > 0.f)
			{
				m_shape.move(sf::Vector2f{ 0.f, intersectY });
				m_collisionDirection.y = 1.0f;
			}
			else
			{
				m_shape.move(sf::Vector2f{ 0.f, -intersectY });
				m_collisionDirection.y = -1.0f;
			}
			m_collisionDirection.x = 0.f;
		}

		return true;
	}

	return false;
}
