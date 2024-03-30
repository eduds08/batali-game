#include "PlayerFallingState.h"

#include "Player.h"

PlayerFallingState::PlayerFallingState()
{
}

PlayerFallingState::~PlayerFallingState()
{
}

IPlayerState* PlayerFallingState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	return nullptr;
}

void PlayerFallingState::update(Player& player)
{
	if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerFallingState::enter(Player& player)
{
	player.animationName = FALLING_ANIMATION;
	player.isLoopingAnimation = true;
	// Set falling texture
}
