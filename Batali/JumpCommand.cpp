#include "JumpCommand.h"

#include "Player.h"

void JumpCommand::execute(Player& player)
{
	player.handleInput(player.JUMP_BUTTON);
}
