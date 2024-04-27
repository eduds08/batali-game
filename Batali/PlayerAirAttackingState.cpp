#include "PlayerAirAttackingState.h"

#include "PlayerFallingState.h"
#include "PlayerHittedState.h"

#include "IAnimationComponent.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerAirAttackingState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "HITTED")
	{
		return std::make_unique<PlayerHittedState>();
	}

	return nullptr;
}

void PlayerAirAttackingState::update(Player& player)
{
	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerFallingState>());
	}
}

void PlayerAirAttackingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, AIR_ATTACK_ANIMATION, false);

	player.m_currentState = "AirAttackingState";
}
