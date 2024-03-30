#pragma once

#include "PlayerAttackingState.h"

class PlayerAttacking2State : public PlayerAttackingState
{
public:
	PlayerAttacking2State() = default;
	virtual ~PlayerAttacking2State() = default;

	virtual void enter(Player& player);
};
