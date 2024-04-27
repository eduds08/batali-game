#include "PlayerUltimateState.h"

#include "PlayerIdleState.h"

#include "IAnimationComponent.h"

#include "PlayerHittedState.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerUltimateState::handleCondition(Player& player, const std::string& condition)
{
	return nullptr;
}

void PlayerUltimateState::update(Player& player)
{
	player.setKnockbackVelocity(0.f);

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerUltimateState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, ULTIMATE_ANIMATION, false);

	player.m_currentState = "UltimateState";
}
