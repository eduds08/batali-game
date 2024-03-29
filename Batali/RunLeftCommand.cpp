#include "RunLeftCommand.h"

#include "Player.h"

void RunLeftCommand::execute(Player& player)
{
	player.m_facingRight = -1;
	player.handleInput(player.RUN_LEFT_BUTTON);
}
