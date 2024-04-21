#include "RunRightCommand.h"

#include "Player.h"

void RunRightCommand::execute(Player& player)
{
	player.handleCondition("RUN_RIGHT_BUTTON");
}
