#include "PlayerIdleState.h"

#include "Player.h"

#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"

PlayerIdleState::PlayerIdleState()
{

}

PlayerIdleState::~PlayerIdleState()
{

}

IPlayerState* PlayerIdleState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	if (input == player.JUMP_BUTTON && !release)
	{
		return new PlayerJumpingState();
	}
	else if (input == player.RUN_RIGHT_BUTTON && !release)
	{
		return new PlayerRunningState();
	}
	else if (input == player.RUN_LEFT_BUTTON && !release)
	{
		return new PlayerRunningState();
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

void PlayerIdleState::update(Player& player)
{

}

void PlayerIdleState::enter(Player& player)
{
	player.animationName = IDLE_ANIMATION;
	player.isLoopingAnimation = true;
	// set player new animation
}
