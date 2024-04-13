#pragma once

#include "IPlayerState.h"

#include "Constants.h"

using namespace constants;

class PlayerDeadState : public IPlayerState
{
public:
	PlayerDeadState() = default;
	virtual ~PlayerDeadState() = default;

	virtual std::unique_ptr<IPlayerState> handleHitted(Player& player, int enemyDamage);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
