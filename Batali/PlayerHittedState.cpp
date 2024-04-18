#include "PlayerHittedState.h"

#include "PlayerIdleState.h"

#include "IAnimationComponent.h"
#include "PlayerDeadState.h"
#include "Player.h"

PlayerHittedState::PlayerHittedState(Player& player)
{
	player.takeDamage(player.m_damageToTake);
}

std::unique_ptr<IPlayerState> PlayerHittedState::handleCondition(Player& player, const std::string& condition)
{
	return nullptr;
}

void PlayerHittedState::update(Player& player)
{
	if (player.m_hp <= 0)
	{
		player.setPlayerState(std::make_unique<PlayerDeadState>());
	}

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerHittedState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, HITTED_ANIMATION, false);
}
