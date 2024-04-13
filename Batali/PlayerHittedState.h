#pragma once

#include "IPlayerState.h"

class PlayerHittedState : public IPlayerState
{
public:
	PlayerHittedState(Player& player, Player& enemy);
	virtual ~PlayerHittedState() = default;

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, Player& enemy);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
