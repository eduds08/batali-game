#include "PlayerAttackingState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "PlayerHittedState.h"
#include "PlayerIdleState.h"

std::unique_ptr<IPlayerState> PlayerAttackingState::handleHitted(Player& player, int enemyDamage, float knockbackVelocity)
{
	return std::make_unique<PlayerHittedState>(player, enemyDamage, knockbackVelocity);
}

std::unique_ptr<IPlayerState> PlayerAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
    return nullptr;
}

void PlayerAttackingState::update(Player& player)
{
	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}
