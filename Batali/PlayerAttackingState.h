#pragma once

#include "IPlayerState.h"

class PlayerAttackingState : public IPlayerState
{
public:
	PlayerAttackingState() = default;
	virtual ~PlayerAttackingState() = default;

	

	
	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player) = 0;
};
