#pragma once

#include "IPlayerState.h"

class PlayerRunningState : public IPlayerState
{
public:
	PlayerRunningState();
	virtual ~PlayerRunningState();

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, int enemyDamage, float knockbackVelocity);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
