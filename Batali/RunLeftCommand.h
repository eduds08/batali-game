#pragma once

#include "ICommand.h"

class RunLeftCommand : public ICommand
{
public:
	RunLeftCommand() = default;
	virtual ~RunLeftCommand() = default;

	virtual void execute(Player& player);
};
