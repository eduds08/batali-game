#pragma once

#include "ColliderEntity.h"

class WalkingEntity : public ColliderEntity
{
public:
	WalkingEntity();
	virtual ~WalkingEntity() = default;

	// Updates some entity's attributes when isCollidingWith() returns true
	void handleCollision();

	// Updates velocity components of the entity according to some conditions
	void updateMovement(bool conditionRunLeft, bool conditionRunRight, bool conditionJump, float& deltaTime, bool conditionRoll = false);

	const bool getOnRoll() const { return m_onRoll; }
	const int* getStamina() const { return &m_stamina; }

	void setConditionRunLeft(bool conditionRunLeft) { m_conditionRunLeft = conditionRunLeft; }
	void setConditionRunRight(bool conditionRunRight) { m_conditionRunRight = conditionRunRight; }
	void setConditionJump(bool conditionJump) { m_conditionJump = conditionJump; }
	void setConditionRoll(bool conditionRoll) { m_conditionRoll = conditionRoll; }

	virtual const bool getHitted() const = 0;
	virtual void setKnockbackVelocity(float knockbackVelocity) = 0;
	virtual const bool getOnWindHashashinUltimate() const = 0;
	virtual const std::string& getAttackMode() const = 0;

protected:
	bool m_conditionRunLeft{ false };
	bool m_conditionRunRight{ false };
	bool m_conditionJump{ false };
	bool m_conditionRoll{ false };

	bool m_canJump{ false };

	bool m_isRunning{ false };

	float m_jumpHeight{};

	bool m_onRoll{ false };

	int m_stamina{ 100 };
	sf::Clock m_staminaRecoverClock{};
	float m_staminaRecoverTime{};
};

