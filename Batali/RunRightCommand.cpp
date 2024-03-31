#include "RunRightCommand.h"

#include "Player.h"

void RunRightCommand::execute(Player& player)
{
	player.handleInput(player.RUN_RIGHT_BUTTON);
}
