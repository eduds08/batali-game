#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class MovableEntity : public AnimatedEntity, public ColliderEntity
{
public:
	MovableEntity(sf::Vector2f firstPosition);
	virtual ~MovableEntity() = default;

	void handleCollision();

	void move(float& deltaTime);

	void updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime);

	void flipSprite() { m_sprite.setScale(m_spriteScale * m_facingRight, m_spriteScale); }

	void updateCanJump() { m_canJump = m_collisionDirection.y > 0.f; }

	virtual bool getInDamageCooldown() = 0;
	virtual bool getIsAttacking() = 0;
protected:
	sf::Vector2f m_velocity{};

	bool m_canJump{ false };

	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	float m_speed{};
};
