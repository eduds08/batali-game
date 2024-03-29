#include "RunRightCommand.h"

#include "Player.h"

void RunRightCommand::execute(Player& player)
{
	player.m_facingRight = 1;
	player.handleInput(player.RUN_RIGHT_BUTTON);
}
