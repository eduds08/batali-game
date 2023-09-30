#pragma once

#include "SFML/Graphics.hpp"

class ColliderEntity
{
public:
	ColliderEntity(float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~ColliderEntity() = default;

	bool isCollidingWith(sf::Sprite& body);

	sf::RectangleShape& getShape() { return m_shape; }

	const sf::Vector2f& getSize() { return m_shape.getSize(); }
	const sf::Vector2f& getPosition() { return m_shape.getPosition(); }

protected:
	sf::RectangleShape m_shape{};
	sf::Vector2f m_collisionDirection{};
};
