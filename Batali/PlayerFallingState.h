#pragma once

#include "IPlayerState.h"

class PlayerFallingState : public IPlayerState
{
public:
	PlayerFallingState();
	virtual ~PlayerFallingState();

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
