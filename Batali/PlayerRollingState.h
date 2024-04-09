#pragma once

#include "IPlayerState.h"

class PlayerRollingState : public IPlayerState
{
public:
	PlayerRollingState();
	virtual ~PlayerRollingState();

	virtual std::unique_ptr<IPlayerState> handleCondition(Player& player, const std::string& condition);

	virtual std::unique_ptr<IPlayerState> handleInput(Player& player, sf::Keyboard::Scancode input);
	virtual void update(Player& player);

	virtual void enter(Player& player);
};
