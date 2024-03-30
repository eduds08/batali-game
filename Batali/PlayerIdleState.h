#pragma once

#include "IPlayerState.h"

class PlayerIdleState : public IPlayerState
{
public:
	PlayerIdleState();
	virtual ~PlayerIdleState();

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);

private:

};
