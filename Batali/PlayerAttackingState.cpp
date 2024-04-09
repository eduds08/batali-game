#include "PlayerAttackingState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "PlayerHittedState.h"
#include "PlayerIdleState.h"

std::unique_ptr<IPlayerState> PlayerAttackingState::handleCondition(Player& player, const std::string& condition)
{
	if (condition == "HITTED")
	{
		return std::make_unique<PlayerHittedState>();
	}

	return nullptr;
}

std::unique_ptr<IPlayerState> PlayerAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
    return nullptr;
}

void PlayerAttackingState::update(Player& player)
{
    // hitbox logic...

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}
