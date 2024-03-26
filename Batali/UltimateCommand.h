#pragma once

#include "Command.h"

class UltimateCommand : public Command
{
public:
	virtual ~UltimateCommand() = default;
	virtual void execute(Character& character);
};

