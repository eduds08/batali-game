#include "PlayerRunningState.h"

#include "Player.h"

PlayerRunningState::PlayerRunningState()
{

}

PlayerRunningState::~PlayerRunningState()
{

}

IPlayerState* PlayerRunningState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	if ((input == player.RUN_LEFT_BUTTON || player.RUN_RIGHT_BUTTON) && release)
	{
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerRunningState::update(Player& player)
{
	player.getVelocity().x = 200.f * player.m_facingRight;
}

void PlayerRunningState::enter(Player& player)
{
	player.animationName = RUNNING_ANIMATION;
}
