#pragma once

#include "IPlayerState.h"

class PlayerAirAttackingState : public IPlayerState
{
public:
	PlayerAirAttackingState() = default;
	virtual ~PlayerAirAttackingState() = default;

	virtual IPlayerState* handleInput(Player& player, sf::Keyboard::Scancode input, bool release = false);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
