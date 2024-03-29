#pragma once

#include <string>

class Player;

class IPlayerState
{
public:
	virtual ~IPlayerState() = default;

	virtual Player* handleInput(Player& player, const std::string& input) = 0;
	virtual void update(Player& player) = 0;

	virtual void enter(Player& player) = 0;
};
