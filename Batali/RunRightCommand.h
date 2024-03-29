#pragma once

#include "ICommand.h"

class RunRightCommand : public ICommand
{
public:
	RunRightCommand() = default;
	virtual ~RunRightCommand() = default;

	virtual void execute(Player& player);
};
