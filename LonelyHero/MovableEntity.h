#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"

class MovableEntity : public AnimatedEntity, public ColliderEntity
{
public:
	MovableEntity(sf::Vector2f firstPosition);
	virtual ~MovableEntity() = default;

	// Updates some entity's attributes when isCollidingWith() returns true
	void handleCollision();

	// Moves the shape and updates the sprite position to the same place
	void move(float& deltaTime);

	// Updates velocity components of the entity according to some conditions
	void updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime);

	void flipSprite() { m_sprite.setScale(m_spriteScale * m_facingRight, m_spriteScale); }

	virtual bool getHitted() = 0;
	virtual bool getIsAttacking() = 0;
	virtual void setKnockbackVelocity(float knockbackVelocity) = 0;
protected:
	sf::Vector2f m_velocity{};

	bool m_canJump{ false };

	bool m_isRunning{ false };

	int m_facingRight{ 1 };

	float m_speed{};
	float m_jumpHeight{};
};
