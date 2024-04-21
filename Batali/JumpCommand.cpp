#include "JumpCommand.h"

#include "Player.h"

void JumpCommand::execute(Player& player)
{
	player.handleCondition("JUMP_BUTTON");
}
