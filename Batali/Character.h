#pragma once

#include "ColliderEntity.h"

class CharacterState;

class Character : public ColliderEntity
{
public:
	Character();
	virtual ~Character() {}

	void handleCondition(const std::string& condition);

	void update(float& deltaTime);

	CharacterState* m_state{ };

	virtual void updateAttackHitbox() = 0;

	bool isCollidingWithAttack(Character& attackingEntity, bool& isUltimateActivate);

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }
	const int getDamage() const { return m_damage; }

	// Updates entity's attributes when it gets attacked (and returns if attackedEntity got hit or not)
	bool takeDamage(float& deltaTime, float attackDirection, int damage);

	// Moves the entity after being hit. attackDirection -> direction of the attack (from left or right)
	void knockbackMove(float& deltaTime, float attackDirection);

	friend class RollingState;
	friend class RunningState;
	friend class JumpingState;
	friend class FallingState;
	friend class IdleState;
	friend class AttackingState;
	friend class OnUltimateState;
	friend class HittedState;
	friend class DeadState;

protected:

	sf::RectangleShape m_attackHitbox{ sf::Vector2f{0.f, 0.f} };

	sf::Vector2f m_attackHitboxPosition{};

	float m_knockbackVelocity{ KNOCKBACK_SPEED };

	float m_attackHitboxWidth{};
	float m_attackHitboxHeight{};

	int m_damage{};

	int m_hp{ 1300 };
};
