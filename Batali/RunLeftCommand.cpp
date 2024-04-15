#include "RunLeftCommand.h"

#include "Player.h"

void RunLeftCommand::execute(Player& player)
{
	player.setFacingRight(-1);
	player.getVelocity().x = 200.f * player.getFacingRight();

	player.handleInput(player.getKeyBinding("RUN_LEFT_BUTTON"));
}
