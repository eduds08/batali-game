#pragma once

#include "ICommand.h"

class JumpCommand : public ICommand
{
public:
	JumpCommand() = default;
	virtual ~JumpCommand() = default;

	virtual void execute(Player& player);
};
