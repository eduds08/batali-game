#include "PlayerAttacking2State.h"

#include "Player.h"

void PlayerAttacking2State::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, ATTACK_2_ANIMATION, false);
}
