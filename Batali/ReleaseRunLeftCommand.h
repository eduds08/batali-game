#pragma once

#include "ICommand.h"

class ReleaseRunLeftCommand : public ICommand
{
public:
	ReleaseRunLeftCommand() = default;
	virtual ~ReleaseRunLeftCommand() = default;

	virtual void execute(Player& player);
};
