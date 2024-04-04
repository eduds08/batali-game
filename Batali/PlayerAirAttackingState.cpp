#include "PlayerAirAttackingState.h"

#include "PlayerFallingState.h"

#include "IAnimationComponent.h"

#include "Player.h"

std::shared_ptr<IPlayerState> PlayerAirAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerAirAttackingState::update(Player& player)
{
	// hitbox logic

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_shared<PlayerFallingState>());
	}
}

void PlayerAirAttackingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, AIR_ATTACK_ANIMATION, false);
}
