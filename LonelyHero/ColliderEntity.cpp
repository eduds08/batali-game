#include "ColliderEntity.h"

ColliderEntity::ColliderEntity(float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
{
	m_shape.setSize(sf::Vector2f{ shapeWidth, shapeHeight });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);
}

bool ColliderEntity::isCollidingWith(sf::Transformable& body)
{
	float groundHalfSizeX{};
	float groundHalfSizeY{};

	if (auto derived = dynamic_cast<sf::Sprite*>(&body))
	{
		float groundHalfSizeX = derived->getTexture()->getSize().x / 2.f;
		float groundHalfSizeY = derived->getTexture()->getSize().y / 2.f;
	}

	else if (auto derived = dynamic_cast<sf::RectangleShape*>(&body))
	{
		float groundHalfSizeX = derived->getSize().x / 2.f;
		float groundHalfSizeY = derived->getSize().y / 2.f;
	}

	float groundPositionX = body.getPosition().x;
	float groundPositionY = body.getPosition().y;

	float entityHalfSizeX = getSize().x / 2.f;
	float entityHalfSizeY = getSize().y / 2.f;
	float entityPositionX = getPosition().x;
	float entityPositionY = getPosition().y;

	float deltaX = groundPositionX - entityPositionX;
	float deltaY = groundPositionY - entityPositionY;

	float intersectX = abs(deltaX) - (groundHalfSizeX + entityHalfSizeX);
	float intersectY = abs(deltaY) - (groundHalfSizeY + entityHalfSizeY);

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
