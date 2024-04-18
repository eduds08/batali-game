#include "RunLeftCommand.h"

#include "Player.h"

void RunLeftCommand::execute(Player& player)
{
	//player.handleInput(player.getKeyBinding("RUN_LEFT_BUTTON"));
	player.handleCondition("RUN_LEFT_BUTTON");
}
