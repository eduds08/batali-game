#include "PlayerUltimateState.h"

#include "PlayerIdleState.h"

#include "Player.h"

IPlayerState* PlayerUltimateState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	return nullptr;
}

void PlayerUltimateState::update(Player& player)
{
	// immortal logic
	// hitbox logic

	if (player.temporarioAnimationEnd)
	{
		player.temporarioAnimationEnd = false;
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerUltimateState::enter(Player& player)
{
	player.animationName = ULTIMATE_ANIMATION;
	player.isLoopingAnimation = false;
}
