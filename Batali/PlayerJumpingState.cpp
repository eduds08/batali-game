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

IPlayerState* PlayerJumpingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if ((input == player.ATTACK_1_BUTTON || input == player.ATTACK_2_BUTTON))
	{
		return new PlayerAirAttackingState();
	}

	return nullptr;
}

void PlayerJumpingState::update(Player& player)
{
	if (sf::Keyboard::isKeyPressed(player.RUN_RIGHT_BUTTON))
	{
		player.setFacingRight(1);
		player.getVelocity().x = 200.f * player.getFacingRight();
	}
	else if (sf::Keyboard::isKeyPressed(player.RUN_LEFT_BUTTON))
	{
		player.setFacingRight(-1);
		player.getVelocity().x = 200.f * player.getFacingRight();
	}

	if (player.getVelocity().y > 0.f)
	{
		player.setPlayerState(new PlayerFallingState());
	}
	else if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerJumpingState::enter(Player& player)
{
	player.getVelocity().y = -1 * sqrt(2.f * GRAVITY * 90.f);

	player.getAnimatingComponent()->setNewAnimation(player, JUMPING_ANIMATION, true);
}
