#include "RunRightCommand.h"

#include "Player.h"

void RunRightCommand::execute(Player& player)
{
	//player.handleInput(player.getKeyBinding("RUN_RIGHT_BUTTON"));
	player.handleCondition("RUN_RIGHT_BUTTON");
}
