#include "PlayerRollingState.h"
#include "PlayerIdleState.h"
#include "IAnimationComponent.h"
#include "Player.h"

PlayerRollingState::PlayerRollingState()
{
}

PlayerRollingState::~PlayerRollingState()
{
}

std::shared_ptr<IPlayerState> PlayerRollingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerRollingState::update(Player& player)
{
	player.getVelocity().x = player.getFacingRight() * 230.f;

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_shared<PlayerIdleState>());
	}
}

void PlayerRollingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, ROLL_ANIMATION, false);
	//player.animationName = ROLL_ANIMATION;
	//player.isLoopingAnimation = false;
}
