#pragma once

#include "AttackHitbox.h"

#include "Constants.h"

class Player;
class World;

using namespace constants;

class PlayerAttackComponent
{
public:
	PlayerAttackComponent() = default;
	virtual ~PlayerAttackComponent() = default;

	virtual void update(World& world, float& deltaTime);

	virtual void enter(Player* player);

protected:
	virtual void updateAttackHitbox();

	virtual void updateAttack1(const int currentPlayerAnimationFrame) = 0;
	virtual void updateAttack2(const int currentPlayerAnimationFrame) = 0;
	virtual void updateAirAttack(const int currentPlayerAnimationFrame) = 0;
	virtual void updateUltimate(const int currentPlayerAnimationFrame) = 0;

	virtual bool isBeingAttackedBy(const AttackHitbox& enemyAttackHitbox);

	virtual const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	virtual void attack(Player& enemy) = 0;

	virtual void knockbackMove(float& deltaTime);

protected:
	AttackHitbox m_attackHitbox{};

	Player* m_thisPlayer{ nullptr };
};
