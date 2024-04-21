#include "RunLeftCommand.h"

#include "Player.h"

void RunLeftCommand::execute(Player& player)
{
	player.handleCondition("RUN_LEFT_BUTTON");
}
