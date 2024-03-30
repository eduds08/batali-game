#include "PlayerAttacking2State.h"

#include "Player.h"

void PlayerAttacking2State::enter(Player& player)
{
	player.animationName = ATTACK_2_ANIMATION;
	player.isLoopingAnimation = false;
}
