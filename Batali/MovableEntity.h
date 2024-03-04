#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"

class MovableEntity : public AnimatedEntity, public ColliderEntity
{
public:
	MovableEntity();
	virtual ~MovableEntity() = default;

	// Updates some entity's attributes when isCollidingWith() returns true
	void handleCollision();

	// Moves the shape and updates the sprite position to the same place
	void move(float& deltaTime);

	// Updates velocity components of the entity according to some conditions
	void updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime, bool conditionRoll=false);

	void flipSprite() { m_sprite.setScale(static_cast<float>(m_facingRight), 1.f); }

	const bool getOnRoll() const { return m_onRoll; }

	void setConditionRunLeft(bool conditionRunLeft) { m_conditionRunLeft = conditionRunLeft; }
	void setConditionRunRight(bool conditionRunRight) { m_conditionRunRight = conditionRunRight; }
	void setConditionJump(bool conditionJump) { m_conditionJump = conditionJump; }
	void setConditionRoll(bool conditionRoll) { m_conditionRoll = conditionRoll; }

	virtual const bool getHitted() const = 0;
	virtual const bool getIsAttacking() const = 0;
	virtual void setKnockbackVelocity(float knockbackVelocity) = 0;

	virtual const bool getOnUltimate() const = 0;

	const int& getStamina() const { return m_stamina; }

protected:
	sf::Vector2f m_velocity{};

	bool m_conditionRunLeft{ false };
	bool m_conditionRunRight{ false };
	bool m_conditionJump{ false };
	bool m_conditionRoll{ false };

	bool m_canJump{ false };

	bool m_isRunning{ false };

	int m_facingRight{ 1 };

	float m_speed{};
	float m_jumpHeight{};

	bool m_onRoll{ false };

	int m_stamina{ 100 };
	sf::Clock m_staminaRecoverClock{};
	float m_staminaRecoverTime{};
};
