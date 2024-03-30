#include "RollCommand.h"

#include "Player.h"

void RollCommand::execute(Player& player)
{
	player.handleInput(player.ROLL_BUTTON);
}
