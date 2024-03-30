#include "PlayerRollingState.h"

#include "Player.h"

PlayerRollingState::PlayerRollingState()
{
}

PlayerRollingState::~PlayerRollingState()
{
}

IPlayerState* PlayerRollingState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	return nullptr;
}

void PlayerRollingState::update(Player& player)
{
	player.getVelocity().x = player.m_facingRight * 230.f;

	if (player.temporarioAnimationEnd)
	{
		player.temporarioAnimationEnd = false;
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerRollingState::enter(Player& player)
{
	player.animationName = ROLL_ANIMATION;
	player.isLoopingAnimation = false;
}
