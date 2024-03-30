#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"

#include "PlayerAirAttackingState.h"

#include "Player.h"

PlayerJumpingState::PlayerJumpingState()
{
}

PlayerJumpingState::~PlayerJumpingState()
{
}

IPlayerState* PlayerJumpingState::handleInput(Player& player, sf::Keyboard::Scancode input, bool release)
{
	if ((input == player.ATTACK_1_BUTTON || input == player.ATTACK_2_BUTTON) && !release)
	{
		return new PlayerAirAttackingState();
	}

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

	player.animationName = JUMPING_ANIMATION;
	player.isLoopingAnimation = true;
}
