#include "ReleaseRunRightCommand.h"

#include "Player.h"

void ReleaseRunRightCommand::execute(Player& player)
{
	player.handleInput(player.RUN_RIGHT_BUTTON, true);
}
