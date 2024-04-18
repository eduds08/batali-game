#include "UltimateCommand.h"

#include "Player.h"

void UltimateCommand::execute(Player& player)
{
	//player.handleInput(player.getKeyBinding("ULTIMATE_BUTTON"));
	player.handleCondition("ULTIMATE_BUTTON");
}
