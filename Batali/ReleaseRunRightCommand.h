#pragma once

#include "ICommand.h"

class ReleaseRunRightCommand : public ICommand
{
public:
	ReleaseRunRightCommand() = default;
	virtual ~ReleaseRunRightCommand() = default;

	virtual void execute(Player& player);
};
