#pragma once

#include "IPlayerState.h"

class PlayerUltimateState : public IPlayerState
{
public:
	PlayerUltimateState() = default;
	virtual ~PlayerUltimateState() = default;

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
