#pragma once

#include "IPlayerState.h"

class PlayerAttackingState : public IPlayerState
{
public:
	PlayerAttackingState() = default;
	virtual ~PlayerAttackingState() = default;

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, int enemyDamage, bool fastHit = false, bool frozen = false);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player) = 0;
};
