#include "RunRightCommand.h"

#include "Player.h"

void RunRightCommand::execute(Player& player)
{
	player.setFacingRight(1);
	player.getVelocity().x = 200.f * player.getFacingRight();

	player.handleInput(player.getKeyBinding("RUN_RIGHT_BUTTON"));
}
