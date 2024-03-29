#include "PlayerJumpingState.h"

#include "Player.h"

PlayerJumpingState::PlayerJumpingState()
{
}

PlayerJumpingState::~PlayerJumpingState()
{
}

IPlayerState* PlayerJumpingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	// change state

	return nullptr;
}

void PlayerJumpingState::update(Player& player)
{
	// Some logic idk yet
}

void PlayerJumpingState::enter(Player& player)
{
	player.getVelocity().y = -1 * sqrt(2.f * GRAVITY * 90.f);
}
