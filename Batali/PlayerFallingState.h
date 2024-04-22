#pragma once

#include "IPlayerState.h"

class PlayerFallingState : public IPlayerState
{
public:
	PlayerFallingState() = default;
	virtual ~PlayerFallingState() = default;
	
	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};
