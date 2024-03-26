#pragma once

#include "Command.h"

class RollCommand : public Command
{
public:
	virtual ~RollCommand() = default;
	virtual void execute(Character& character);
};
