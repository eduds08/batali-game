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
		player.m_facingRight = 1;
		return new PlayerRunningState();
	}
	else if (input == player.RUN_LEFT_BUTTON)
	{
		player.m_facingRight = -1;
		return new PlayerRunningState();
	}

	return nullptr;
}

void PlayerIdleState::update(Player& player)
{

}

void PlayerIdleState::enter(Player& player)
{
	// set player new animation
}
