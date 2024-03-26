#pragma once

#include "Command.h"

class RunCommand : public Command
{
public:
	virtual ~RunCommand() = default;
	virtual void execute(Character& character);
};

