#pragma once

#include "IPlayerState.h"

class PlayerIdleState : public IPlayerState
{
public:
	PlayerIdleState();
	virtual ~PlayerIdleState();

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
