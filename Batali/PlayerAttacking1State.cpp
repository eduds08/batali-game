#include "PlayerAttacking1State.h"

#include "Player.h"

void PlayerAttacking1State::enter(Player& player)
{
	player.animationName = ATTACK_1_ANIMATION;
	player.isLoopingAnimation = false;
}
