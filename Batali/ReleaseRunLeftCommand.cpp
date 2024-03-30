#include "ReleaseRunLeftCommand.h"

#include "Player.h"

void ReleaseRunLeftCommand::execute(Player& player)
{
	player.handleInput(player.RUN_LEFT_BUTTON, true);
}
