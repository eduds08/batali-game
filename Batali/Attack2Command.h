#pragma once

#include "Command.h"

class Attack2Command : public Command
{
public:
	virtual ~Attack2Command() = default;
	virtual void execute(Character& character);
};

