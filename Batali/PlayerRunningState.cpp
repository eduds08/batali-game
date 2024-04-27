#include "PlayerRunningState.h"

#include "PlayerJumpingState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"
#include "PlayerIdleState.h"
#include "PlayerHittedState.h"

#include "IAnimationComponent.h"
#include "Player.h"

std::unique_ptr<IPlayerState> PlayerRunningState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "JUMP_BUTTON")
	{
		return std::make_unique<PlayerJumpingState>();
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
	else if (condition == "RUN_RIGHT_BUTTON")
	{
		player.setFacingRight(1);
		player.getVelocity().x = player.getSpeed() * player.getFacingRight();
	}
	else if (condition == "RUN_LEFT_BUTTON")
	{
		player.setFacingRight(-1);
		player.getVelocity().x = player.getSpeed() * player.getFacingRight();
	}
	else if (condition == "HITTED")
	{
		return std::make_unique<PlayerHittedState>();
	}

	return nullptr;
}

void PlayerRunningState::update(Player& player)
{
	if (player.getVelocity().x == 0.f)
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerRunningState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, RUNNING_ANIMATION, true);
	player.getVelocity().x = 1.f;

	player.m_currentState = "RunningState";
}
