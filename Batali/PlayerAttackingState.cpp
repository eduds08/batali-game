#include "PlayerAttackingState.h"
#include "IAnimationComponent.h"
#include "Player.h"

#include "PlayerIdleState.h"

IPlayerState* PlayerAttackingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
    return nullptr;
}

void PlayerAttackingState::update(Player& player)
{
    // hitbox logic...

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(new PlayerIdleState());
	}
}
