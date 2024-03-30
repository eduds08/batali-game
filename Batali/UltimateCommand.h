#pragma once

#include "ICommand.h"

class UltimateCommand : public ICommand
{
public:
	UltimateCommand() = default;
	virtual ~UltimateCommand() = default;

	virtual void execute(Player& player);
};
