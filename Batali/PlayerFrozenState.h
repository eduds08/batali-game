#pragma once

#include "IPlayerState.h"

class PlayerFrozenState : public IPlayerState
{
public:
	PlayerFrozenState() = default;
	virtual ~PlayerFrozenState() = default;

	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};

