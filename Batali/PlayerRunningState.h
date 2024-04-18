#pragma once

#include "IPlayerState.h"

class PlayerRunningState : public IPlayerState
{
public:
	PlayerRunningState();
	virtual ~PlayerRunningState();

	

	
	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};
