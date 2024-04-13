#include "PlayerAirAttackingState.h"

#include "PlayerFallingState.h"
#include "PlayerHittedState.h"

#include "IAnimationComponent.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerAirAttackingState::handleHitted(Player& player, Player& enemy)
{
	return std::make_unique<PlayerHittedState>(player, enemy);
}

std::unique_ptr<IPlayerState> PlayerAirAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerAirAttackingState::update(Player& player)
{
	// hitbox logic

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerFallingState>());
	}
}

void PlayerAirAttackingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, AIR_ATTACK_ANIMATION, false);
}
