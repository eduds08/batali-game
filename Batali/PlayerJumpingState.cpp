#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include "PlayerIdleState.h"
#include "PlayerAirAttackingState.h"
#include "PlayerHittedState.h"
#include "IAnimationComponent.h"

#include "Player.h"

PlayerJumpingState::PlayerJumpingState()
{
}

PlayerJumpingState::~PlayerJumpingState()
{
}

std::unique_ptr<IPlayerState> PlayerJumpingState::handleHitted(Player& player, int enemyDamage, bool fastHit, bool frozen)
{
	return std::make_unique<PlayerHittedState>(player, enemyDamage, fastHit, frozen);
}

std::unique_ptr<IPlayerState> PlayerJumpingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if ((input == player.getKeyBinding("ATTACK_1_BUTTON") || input == player.getKeyBinding("ATTACK_2_BUTTON")))
	{
		return std::make_unique<PlayerAirAttackingState>();
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
		player.setPlayerState(std::make_unique<PlayerFallingState>());
	}
	else if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerJumpingState::enter(Player& player)
{
	player.getVelocity().y = -1 * sqrt(2.f * GRAVITY * 90.f);

	player.getAnimationComponent()->setNewAnimation(player, JUMPING_ANIMATION, true);
}
