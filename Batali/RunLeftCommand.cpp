#include "RunLeftCommand.h"

#include "Player.h"

void RunLeftCommand::execute(Player& player)
{
	player.handleInput(player.RUN_LEFT_BUTTON);
}
