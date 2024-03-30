#include "UltimateCommand.h"

#include "Player.h"

void UltimateCommand::execute(Player& player)
{
	player.handleInput(player.ULTIMATE_BUTTON);
}
