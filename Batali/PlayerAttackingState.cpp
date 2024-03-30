#include "PlayerAttackingState.h"

#include "Player.h"

IPlayerState* PlayerAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
    return nullptr;
}

void PlayerAttackingState::update(Player& player)
{
    // hitbox logic...

	if (player.temporarioAnimationEnd)
	{
		player.temporarioAnimationEnd = false;
		player.setPlayerState(new PlayerIdleState());
	}
}
