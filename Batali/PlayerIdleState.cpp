#include "PlayerIdleState.h"

#include "Player.h"

#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"

PlayerIdleState::PlayerIdleState()
{

}

PlayerIdleState::~PlayerIdleState()
{

}

IPlayerState* PlayerIdleState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if (input == player.JUMP_BUTTON)
	{
		return new PlayerJumpingState();
	}
	else if (input == player.RUN_RIGHT_BUTTON)
	{
		return new PlayerRunningState();
	}
	else if (input == player.RUN_LEFT_BUTTON)
	{
		return new PlayerRunningState();
	}

	return nullptr;
}

void PlayerIdleState::update(Player& player)
{

}

void PlayerIdleState::enter(Player& player)
{
	player.animationName = IDLE_ANIMATION;
	// set player new animation
}
