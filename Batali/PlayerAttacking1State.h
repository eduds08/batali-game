#pragma once

#include "PlayerAttackingState.h"

class PlayerAttacking1State : public PlayerAttackingState
{
public:
	PlayerAttacking1State() = default;
	virtual ~PlayerAttacking1State() = default;

	virtual void enter(Player& player);
};
