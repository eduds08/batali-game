#pragma once

#include "ICommand.h"

class Attack1Command : public ICommand
{
public:
	Attack1Command() = default;
	virtual ~Attack1Command() = default;

	virtual void execute(Player& player);
};
