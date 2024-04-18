#include "Attack1Command.h"

#include "Player.h"

void Attack1Command::execute(Player& player)
{
	//player.handleInput(player.getKeyBinding("ATTACK_1_BUTTON"));
	player.handleCondition("ATTACK_1_BUTTON");
}
