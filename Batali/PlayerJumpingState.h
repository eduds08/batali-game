#pragma once

#include "IPlayerState.h"

class PlayerJumpingState : public IPlayerState
{
public:
	PlayerJumpingState();
	virtual ~PlayerJumpingState();

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
