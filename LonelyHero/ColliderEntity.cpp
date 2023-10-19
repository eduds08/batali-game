#include "ColliderEntity.h"

//Returns true if colliding with other, false if not. Also set the collision directions (if is colliding in the right, left, bottom or top)
bool ColliderEntity::isCollidingWith(sf::Sprite& other)
{
	float otherHalfSizeX = other.getTexture()->getSize().x / 2.f;
	float otherHalfSizeY = other.getTexture()->getSize().y / 2.f;
	float otherPositionX = other.getPosition().x;
	float otherPositionY = other.getPosition().y;

	float thisHalfSizeX = getSize().x / 2.f;
	float thisHalfSizeY = getSize().y / 2.f;
	float thisPositionX = getPosition().x;
	float thisPositionY = getPosition().y;

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
			setIsCollidingHorizontally(true);
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

// Sets the values of the imaginary view of an entity. Useful to call isCollidingWith() with less tiles (only the ones inside the limits)
void ColliderEntity::updateLimits()
{
	// Limit is set to 5 tiles in each direction (top, right, bottom left) from the center of entity's shape
	int tilesAmount = 5;

	m_rightLimit = m_shape.getPosition().x + tilesAmount * constants::tileSizeF;
	m_leftLimit = m_shape.getPosition().x - tilesAmount * constants::tileSizeF;

	m_topLimit = m_shape.getPosition().y - tilesAmount * constants::tileSizeF;
	m_bottomLimit = m_shape.getPosition().y + tilesAmount * constants::tileSizeF;
}
