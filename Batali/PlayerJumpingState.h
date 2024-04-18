#pragma once

#include "IPlayerState.h"

class PlayerJumpingState : public IPlayerState
{
public:
	PlayerJumpingState();
	virtual ~PlayerJumpingState();

	

	
	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};
