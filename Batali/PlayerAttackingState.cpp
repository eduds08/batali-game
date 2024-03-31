#include "PlayerAttackingState.h"

#include "Player.h"

IPlayerState* PlayerAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
    return nullptr;
}

void PlayerAttackingState::update(Player& player)
{
    // hitbox logic...

	if (player.getAnimatingComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(new PlayerIdleState());
	}
}
