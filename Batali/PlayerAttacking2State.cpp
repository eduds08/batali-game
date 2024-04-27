#include "PlayerAttacking2State.h"
#include "IAnimationComponent.h"
#include "Player.h"

void PlayerAttacking2State::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, ATTACK_2_ANIMATION, false);

	player.m_currentState = "Attacking2State";
}
