#include "PlayerUltimateState.h"

#include "PlayerIdleState.h"

#include "Player.h"

IPlayerState* PlayerUltimateState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerUltimateState::update(Player& player)
{
	// immortal logic
	// hitbox logic

	if (player.getAnimatingComponent()->getIsCurrentAnimationEnd())
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerUltimateState::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, ULTIMATE_ANIMATION, false);
}
