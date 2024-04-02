#include "RollCommand.h"

#include "Player.h"

void RollCommand::execute(Player& player)
{
	player.handleInput(player.getKeyBinding("ROLL_BUTTON"));
}
