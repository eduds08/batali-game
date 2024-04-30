#include "PlayerFrozenState.h"

#include "PlayerIdleState.h"
#include "Player.h"
#include "IAnimationComponent.h"
#include "PlayerDeadState.h"

std::unique_ptr<IPlayerState> PlayerFrozenState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return std::make_unique<PlayerIdleState>();
	}
	else if (condition == "HITTED" && player.getAnimationComponent()->getCurrentAnimation()->getName() != HITTED_ANIMATION)
	{
		player.getAnimationComponent()->setNewAnimation(player, HITTED_ANIMATION, false);
		player.takeDamage();
	}

	return nullptr;
}

void PlayerFrozenState::update(Player& player)
{
	player.setVelocity(0.f, 0.f);

	if (player.getAnimationComponent()->getCurrentAnimation()->getName() == HITTED_ANIMATION && player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.getAnimationComponent()->setNewAnimation(player, IDLE_ANIMATION, true);
	}

	if (player.getHp() <= 0)
	{
		player.setPlayerState(std::make_unique<PlayerDeadState>());
	}
}

void PlayerFrozenState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, IDLE_ANIMATION, true);

	player.m_currentState = "FrozenState";
}
