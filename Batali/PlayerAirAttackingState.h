#pragma once

#include "IPlayerState.h"

class PlayerAirAttackingState : public IPlayerState
{
public:
	PlayerAirAttackingState() = default;
	virtual ~PlayerAirAttackingState() = default;

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, int enemyDamage, float knockbackVelocity, bool fastHit = false, bool frozen = false);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
