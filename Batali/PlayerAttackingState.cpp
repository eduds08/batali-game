#include "PlayerAttackingState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "PlayerHittedState.h"
#include "PlayerIdleState.h"

std::unique_ptr<IPlayerState> PlayerAttackingState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "HITTED")
	{
		return std::make_unique<PlayerHittedState>(player);
	}

	return nullptr;
}

void PlayerAttackingState::update(Player& player)
{
	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}
