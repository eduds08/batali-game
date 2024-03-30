#include "PlayerRunningState.h"

#include "Player.h"

PlayerRunningState::PlayerRunningState()
{

}

PlayerRunningState::~PlayerRunningState()
{

}

IPlayerState* PlayerRunningState::handleInput(Player& player, sf::Keyboard::Scancode input)
{

	return nullptr;
}

void PlayerRunningState::update(Player& player)
{
	player.getVelocity().x = 200.f * player.m_facingRight;

	if (!sf::Keyboard::isKeyPressed(player.RUN_LEFT_BUTTON) && !sf::Keyboard::isKeyPressed(player.RUN_RIGHT_BUTTON))
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerRunningState::enter(Player& player)
{
	player.animationName = RUNNING_ANIMATION;
}
