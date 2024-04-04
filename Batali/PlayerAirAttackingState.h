#pragma once

#include "IPlayerState.h"

class PlayerAirAttackingState : public IPlayerState
{
public:
	PlayerAirAttackingState() = default;
	virtual ~PlayerAirAttackingState() = default;

	virtual std::shared_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
