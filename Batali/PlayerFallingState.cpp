#include "PlayerFallingState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerHittedState.h"

std::unique_ptr<IPlayerState> PlayerFallingState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "RUN_RIGHT_BUTTON")
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

void PlayerFallingState::update(Player& player)
{
	if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerFallingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, FALLING_ANIMATION, true);

	player.m_currentState = "FallingState";
}
