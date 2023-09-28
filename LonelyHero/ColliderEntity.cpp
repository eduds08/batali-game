#include "ColliderEntity.h"

ColliderEntity::ColliderEntity(float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: m_shapeWidth{ shapeWidth }
	, m_shapeHeight{ shapeHeight }
{
	setShapeSettings(firstPosition);
}

bool ColliderEntity::isColliding(const sf::RectangleShape& shape)
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

bool ColliderEntity::isColliding(const sf::Sprite& sprite)
{
	float groundHalfSizeX = sprite.getTexture()->getSize().x / 2.f;
	float groundHalfSizeY = sprite.getTexture()->getSize().y / 2.f;
	float groundPositionX = sprite.getPosition().x;
	float groundPositionY = sprite.getPosition().y;

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

void ColliderEntity::handleCollision()
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

void ColliderEntity::setShapeSettings(sf::Vector2f position)
{
	m_shape.setSize(sf::Vector2f{ m_shapeWidth, m_shapeHeight });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(position.x, position.y);

	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);
}
