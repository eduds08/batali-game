#pragma once

#include "Command.h"

class Attack1Command : public Command
{
public:
	virtual ~Attack1Command() = default;
	virtual void execute(Character& character);
};

