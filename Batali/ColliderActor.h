#pragma once

#include "MovableActor.h"

class ColliderActor : public MovableActor
{
public:
	ColliderActor();
	virtual ~ColliderActor() = default;

	// Checks if colliding with other, if so, it calls handleCollision. Also set the collision directions (if is colliding on the right, left, bottom or top)
	void updateCollisionWith(const sf::Sprite& other);

	// Updates some actor's attributes when updateCollisionWith() checks a collision
	void handleCollision();

	// Moves the actor after being hit. attackDirection -> direction of the attack (from left or right)
	void knockbackMove(float& deltaTime, float attackDirection);

	/* Setters */

	void setIsCollidingHorizontally(bool isCollildingHorizontally) { m_isCollidingHorizontally = isCollildingHorizontally; }
	void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }

	/* Getters */

	const bool getIsCollidingHorizontally() const { return m_isCollidingHorizontally; }

protected:
	sf::Vector2f m_collisionDirection{};

	// Useful to make the actor stops when it is pushed against a wall after being knockbacked
	bool m_isCollidingHorizontally{ false };

	float m_knockbackVelocity{ KNOCKBACK_SPEED };
};
