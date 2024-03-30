#pragma once

#include "IPlayerState.h"

class PlayerRunningState : public IPlayerState
{
public:
	PlayerRunningState();
	virtual ~PlayerRunningState();

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
