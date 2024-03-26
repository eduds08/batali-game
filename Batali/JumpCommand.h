#pragma once

#include "Command.h"

class JumpCommand : public Command
{
public:
	virtual ~JumpCommand() = default;
	virtual void execute(Character& character);
};
