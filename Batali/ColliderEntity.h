#pragma once

#include "MovableEntity.h"

class ColliderEntity : public MovableEntity
{
public:
	ColliderEntity();
	virtual ~ColliderEntity() = default;

	// Returns true if colliding with other, false if not. Also set the collision directions (if is colliding in the right, left, bottom or top)
	bool isCollidingWith(const sf::Sprite& other);

	/* Setters */

	void setIsCollidingHorizontally(bool isCollildingHorizontally) { m_isCollidingHorizontally = isCollildingHorizontally; }

	/* Getters */

	const bool getIsCollidingHorizontally() const { return m_isCollidingHorizontally; }

protected:
	sf::Vector2f m_collisionDirection{};

	// Useful to make the entity stops when it is pushed against a wall after being knockbacked
	bool m_isCollidingHorizontally{ false };
};
