#include "PlayerAttacking1State.h"

#include "IAnimationComponent.h"

#include "Player.h"

void PlayerAttacking1State::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, ATTACK_1_ANIMATION, false);
}
