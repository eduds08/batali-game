#pragma once

#include "IPlayerState.h"

class PlayerHittedState : public IPlayerState
{
public:
	PlayerHittedState() = default;
	virtual ~PlayerHittedState() = default;

	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual void update(Player& player);

	virtual void enter(Player& player);
};
