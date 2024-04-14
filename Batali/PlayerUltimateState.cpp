#include "PlayerUltimateState.h"

#include "PlayerIdleState.h"

#include "IAnimationComponent.h"

#include "PlayerHittedState.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerUltimateState::handleHitted(Player& player, int enemyDamage, bool fastHit, bool frozen)
{
	return nullptr;
}

std::unique_ptr<IPlayerState> PlayerUltimateState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerUltimateState::update(Player& player)
{
	// hitbox logic

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerUltimateState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, ULTIMATE_ANIMATION, false);
}
