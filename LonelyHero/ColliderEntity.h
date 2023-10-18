#pragma once

#include "SFML/Graphics.hpp"

class ColliderEntity
{
public:
	ColliderEntity(sf::Vector2f firstPosition);
	virtual ~ColliderEntity() = default;

	bool isCollidingWith(sf::Sprite& body);

	sf::RectangleShape& getShape() { return m_shape; }

	const sf::Vector2f& getSize() { return m_shape.getSize(); }
	const sf::Vector2f& getPosition() { return m_shape.getPosition(); }

	void setCollidingHorizontallyToTrue() { m_isCollidingHorizontally = true; }
	void resetCollidingHorizontally() { m_isCollidingHorizontally = false; }

protected:
	sf::RectangleShape m_shape{};
	sf::Vector2f m_collisionDirection{};

	bool m_isCollidingHorizontally{ false };
};
