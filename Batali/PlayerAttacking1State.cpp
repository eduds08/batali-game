#include "PlayerAttacking1State.h"

#include "Player.h"

void PlayerAttacking1State::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, ATTACK_1_ANIMATION, false);
}
