#pragma once

class Player;

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual void execute(Player& player) = 0;
};
