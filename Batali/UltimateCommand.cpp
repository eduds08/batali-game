#include "UltimateCommand.h"

#include "Player.h"

void UltimateCommand::execute(Player& player)
{
	player.handleCondition("ULTIMATE_BUTTON");
}
