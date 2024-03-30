#pragma once

#include "IPlayerState.h"

class PlayerRollingState : public IPlayerState
{
public:
	PlayerRollingState();
	virtual ~PlayerRollingState();

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
