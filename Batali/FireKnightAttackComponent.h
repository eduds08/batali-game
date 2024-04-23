#pragma once

#include "PlayerAttackComponent.h"

class FireKnightAttackComponent : public PlayerAttackComponent
{
public:
	FireKnightAttackComponent();
	virtual ~FireKnightAttackComponent() = default;

protected:
	virtual void updateAttack1(const int currentPlayerAnimationFrame);
	virtual void updateAttack2(const int currentPlayerAnimationFrame);
	virtual void updateAirAttack(const int currentPlayerAnimationFrame);
	virtual void updateUltimate(const int currentPlayerAnimationFrame);

	virtual void attack(Player& enemy);
};
