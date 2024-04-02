#include "JumpCommand.h"

#include "Player.h"

void JumpCommand::execute(Player& player)
{
	player.handleInput(player.getKeyBinding("JUMP_BUTTON"));
}
