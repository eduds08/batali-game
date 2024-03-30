#include "PlayerRunningState.h"

#include "PlayerJumpingState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"

#include "Player.h"

PlayerRunningState::PlayerRunningState()
{

}

PlayerRunningState::~PlayerRunningState()
{

}

IPlayerState* PlayerRunningState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	if ((input == player.RUN_LEFT_BUTTON || player.RUN_RIGHT_BUTTON) && release)
	{
		return new PlayerIdleState();
	}
	else if (input == player.JUMP_BUTTON && !release)
	{
		return new PlayerJumpingState();
	}
	else if (input == player.ROLL_BUTTON && !release)
	{
		return new PlayerRollingState();
	}
	else if (input == player.ATTACK_1_BUTTON && !release)
	{
		return new PlayerAttacking1State();
	}
	else if (input == player.ATTACK_2_BUTTON && !release)
	{
		return new PlayerAttacking2State();
	}
	else if (input == player.ULTIMATE_BUTTON && !release)
	{
		return new PlayerUltimateState();
	}

	return nullptr;
}

void PlayerRunningState::update(Player& player)
{
	player.getVelocity().x = 200.f * player.m_facingRight;
}

void PlayerRunningState::enter(Player& player)
{
	player.animationName = RUNNING_ANIMATION;
	player.isLoopingAnimation = true;
}
