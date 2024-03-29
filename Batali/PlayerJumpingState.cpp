#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"

#include "Player.h"

PlayerJumpingState::PlayerJumpingState()
{
}

PlayerJumpingState::~PlayerJumpingState()
{
}

IPlayerState* PlayerJumpingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerJumpingState::update(Player& player)
{
	if (player.getVelocity().y > 0.f)
	{
		player.setPlayerState(new PlayerFallingState());
	}
}

void PlayerJumpingState::enter(Player& player)
{
	player.getVelocity().y = -1 * sqrt(2.f * GRAVITY * 90.f);

	// Set jump texture
}
