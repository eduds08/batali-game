#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.h"

class ColliderEntity
{
public:
	ColliderEntity(sf::Vector2f firstPosition) {}
	virtual ~ColliderEntity() = default;

	bool isCollidingWith(sf::Sprite& other);

	void updateLimits();

	sf::RectangleShape& getShape() { return m_shape; }

	const sf::Vector2f& getSize() { return m_shape.getSize(); }
	const sf::Vector2f& getPosition() { return m_shape.getPosition(); }

	void setIsCollidingHorizontally(bool isCollildingHorizontally) { m_isCollidingHorizontally = isCollildingHorizontally; }
	bool getIsCollidingHorizontally() { return m_isCollidingHorizontally; }

	float m_rightLimit{};
	float m_leftLimit{};
	float m_topLimit{};
	float m_bottomLimit{};

protected:
	sf::RectangleShape m_shape{};
	sf::Vector2f m_collisionDirection{};

	// Useful to make the entity stops when it is pushed against a wall after being attacked
	bool m_isCollidingHorizontally{ false };
};
