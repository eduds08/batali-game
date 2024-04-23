#pragma once

#include "PlayerAttackComponent.h"

class BoxerAttackComponent : public PlayerAttackComponent
{
public:
	BoxerAttackComponent() = default;
	virtual ~BoxerAttackComponent() = default;

private:
	virtual void updateAttack1(const int currentPlayerAnimationFrame);
	virtual void updateAttack2(const int currentPlayerAnimationFrame);
	virtual void updateAirAttack(const int currentPlayerAnimationFrame);
	virtual void updateUltimate(const int currentPlayerAnimationFrame);

	virtual void attack(Player& enemy);
};
