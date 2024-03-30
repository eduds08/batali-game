#include "PlayerAirAttackingState.h"

#include "PlayerFallingState.h"

#include "Player.h"

IPlayerState* PlayerAirAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	return nullptr;
}

void PlayerAirAttackingState::update(Player& player)
{
	// hitbox logic

	if (player.temporarioAnimationEnd)
	{
		player.temporarioAnimationEnd = false;
		player.setPlayerState(new PlayerFallingState());
	}
}

void PlayerAirAttackingState::enter(Player& player)
{
	player.animationName = AIR_ATTACK_ANIMATION;
	player.isLoopingAnimation = false;
}
