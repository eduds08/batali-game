#pragma once

#include "ICommand.h"

class RollCommand : public ICommand
{
public:
	RollCommand() = default;
	virtual ~RollCommand() = default;

	virtual void execute(Player& player);
};
