#include "PlayerAirAttackingState.h"

#include "PlayerFallingState.h"

#include "Player.h"

IPlayerState* PlayerAirAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerAirAttackingState::update(Player& player)
{
	// hitbox logic

	if (player.getAnimatingComponent()->getIsCurrentAnimationEnd())
	{
		player.setPlayerState(new PlayerFallingState());
	}
}

void PlayerAirAttackingState::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, AIR_ATTACK_ANIMATION, false);
}
