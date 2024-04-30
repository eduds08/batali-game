#include "PlayerIdleState.h"

#include "Player.h"

#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"
#include "IAnimationComponent.h"
#include "PlayerHittedState.h"
#include "PlayerFallingState.h"
#include "PlayerFrozenState.h"

std::unique_ptr<IPlayerState> PlayerIdleState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "JUMP_BUTTON")
	{
		return std::make_unique<PlayerJumpingState>();
	}
	else if (condition == "RUN_RIGHT_BUTTON")
	{
		return std::make_unique<PlayerRunningState>();
	}
	else if (condition == "RUN_LEFT_BUTTON")
	{
		return std::make_unique<PlayerRunningState>();
	}
	else if (condition == "ROLL_BUTTON")
	{
		return std::make_unique<PlayerRollingState>();
	}
	else if (condition == "ATTACK_1_BUTTON")
	{
		return std::make_unique<PlayerAttacking1State>();
	}
	else if (condition == "ATTACK_2_BUTTON")
	{
		return std::make_unique<PlayerAttacking2State>();
	}
	else if (condition == "ULTIMATE_BUTTON")
	{
		return std::make_unique<PlayerUltimateState>();
	}
	else if (condition == "HITTED")
	{
		return std::make_unique<PlayerHittedState>();
	}
	else if (condition == "FROZEN")
	{
		return std::make_unique<PlayerFrozenState>();
	}

	return nullptr;
}

void PlayerIdleState::update(Player& player)
{
}

void PlayerIdleState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, IDLE_ANIMATION, true);

	player.m_currentState = "IdleState";
}
