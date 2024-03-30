#pragma once

#include "ICommand.h"

class Attack2Command : public ICommand
{
public:
	Attack2Command() = default;
	virtual ~Attack2Command() = default;

	virtual void execute(Player& player);
};
