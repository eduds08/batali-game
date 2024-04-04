#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include "PlayerIdleState.h"
#include "PlayerAirAttackingState.h"

#include "IAnimationComponent.h"

#include "Player.h"

PlayerJumpingState::PlayerJumpingState()
{
}

PlayerJumpingState::~PlayerJumpingState()
{
}

std::shared_ptr<IPlayerState> PlayerJumpingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if ((input == player.getKeyBinding("ATTACK_1_BUTTON") || input == player.getKeyBinding("ATTACK_2_BUTTON")))
	{
		return std::make_shared<PlayerAirAttackingState>();
	}

	return nullptr;
}

void PlayerJumpingState::update(Player& player)
{
	if (sf::Keyboard::isKeyPressed(player.getKeyBinding("RUN_RIGHT_BUTTON")))
	{
		player.setFacingRight(1);
		player.getVelocity().x = 200.f * player.getFacingRight();
	}
	else if (sf::Keyboard::isKeyPressed(player.getKeyBinding("RUN_LEFT_BUTTON")))
	{
		player.setFacingRight(-1);
		player.getVelocity().x = 200.f * player.getFacingRight();
	}

	if (player.getVelocity().y > 0.f)
	{
		player.setPlayerState(std::make_shared<PlayerFallingState>());
	}
	else if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(std::make_shared<PlayerIdleState>());
	}
}

void PlayerJumpingState::enter(Player& player)
{
	player.getVelocity().y = -1 * sqrt(2.f * GRAVITY * 90.f);

	player.getAnimationComponent()->setNewAnimation(player, JUMPING_ANIMATION, true);
}
