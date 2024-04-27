#include "PlayerRollingState.h"
#include "PlayerIdleState.h"
#include "IAnimationComponent.h"
#include "PlayerHittedState.h"
#include "Player.h"

std::unique_ptr<IPlayerState> PlayerRollingState::handleCondition(Player& player, const std::string& condition)
{
	return nullptr;
}

void PlayerRollingState::update(Player& player)
{
	player.getVelocity().x = player.getFacingRight() * player.getRollSpeed();

	player.setKnockbackVelocity(0.f);

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerRollingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, ROLL_ANIMATION, false);

	player.m_currentState = "RollingState";
}
