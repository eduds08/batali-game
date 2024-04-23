#pragma once

#include "PlayerAttackComponent.h"

class FireKnightAttackComponent : public PlayerAttackComponent
{
public:
	FireKnightAttackComponent() = default;
	virtual ~FireKnightAttackComponent() = default;

private:
	virtual void updateAttack1(const int currentPlayerAnimationFrame);
	virtual void updateAttack2(const int currentPlayerAnimationFrame);
	virtual void updateAirAttack(const int currentPlayerAnimationFrame);
	virtual void updateUltimate(const int currentPlayerAnimationFrame);

	virtual void attack(Player& enemy);
};
