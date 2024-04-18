#pragma once

#include "IPlayerState.h"

class PlayerAirAttackingState : public IPlayerState
{
public:
	PlayerAirAttackingState() = default;
	virtual ~PlayerAirAttackingState() = default;

	

	
	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};
