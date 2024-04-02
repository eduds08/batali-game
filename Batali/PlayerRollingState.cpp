#include "PlayerRollingState.h"

#include "Player.h"

PlayerRollingState::PlayerRollingState()
{
}

PlayerRollingState::~PlayerRollingState()
{
}

IPlayerState* PlayerRollingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerRollingState::update(Player& player)
{
	player.getVelocity().x = player.getFacingRight() * 230.f;

	if (player.getAnimatingComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerRollingState::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, ROLL_ANIMATION, false);
	//player.animationName = ROLL_ANIMATION;
	//player.isLoopingAnimation = false;
}
