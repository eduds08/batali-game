#pragma once

#include "IPlayerState.h"

class PlayerAttackingState : public IPlayerState
{
public:
	PlayerAttackingState() = default;
	virtual ~PlayerAttackingState() = default;

	virtual std::shared_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player) = 0;
};
