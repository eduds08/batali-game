#pragma once

#include "IPlayerState.h"

class PlayerIdleState : public IPlayerState
{
public:
	PlayerIdleState();
	virtual ~PlayerIdleState();

	virtual Player* handleInput(Player& player, const std::string& input);
	virtual void update(Player& player);

	virtual void enter(Player& player);

private:

};
