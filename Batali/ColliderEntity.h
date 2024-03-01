#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.h"

using namespace constants;

class ColliderEntity
{
public:
	ColliderEntity() {}
	virtual ~ColliderEntity() = default;

	//Returns true if colliding with other, false if not. Also set the collision directions (if is colliding in the right, left, bottom or top)
	bool isCollidingWith(const sf::Sprite& other);

	// Sets the values of the imaginary view of an entity. Useful to call isCollidingWith() with less tiles (only the ones inside the limits)
	void updateLimits();

	const sf::RectangleShape& getShape() const { return m_shape; }
	const sf::Vector2f& getShapeSize() const { return m_shape.getSize(); }

	void setShapePosition(sf::Vector2f position) { m_shape.setPosition(position); }
	const sf::Vector2f& getShapePosition() const { return m_shape.getPosition(); }

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
