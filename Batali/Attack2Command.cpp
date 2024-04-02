#include "Attack2Command.h"

#include "Player.h"

void Attack2Command::execute(Player& player)
{
	player.handleInput(player.getKeyBinding("ATTACK_2_BUTTON"));
}
