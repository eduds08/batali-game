#pragma once

#include "IPlayerState.h"

#include "Constants.h"

using namespace constants;

class PlayerDeadState : public IPlayerState
{
public:
	PlayerDeadState() = default;
	virtual ~PlayerDeadState() = default;
	
	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};
