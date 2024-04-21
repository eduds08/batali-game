#include "RollCommand.h"

#include "Player.h"

void RollCommand::execute(Player& player)
{
	player.handleCondition("ROLL_BUTTON");
}
