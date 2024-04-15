#include "PlayerFallingState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerHittedState.h"

PlayerFallingState::PlayerFallingState()
{
}

PlayerFallingState::~PlayerFallingState()
{
}

std::unique_ptr<IPlayerState> PlayerFallingState::handleHitted(Player& player, int enemyDamage, float knockbackVelocity, bool fastHit, bool frozen)
{
	return std::make_unique<PlayerHittedState>(player, enemyDamage, knockbackVelocity, fastHit, frozen);
}

std::unique_ptr<IPlayerState> PlayerFallingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if (input == player.getKeyBinding("RUN_RIGHT_BUTTON"))
	{
		player.setFacingRight(1);
		player.getVelocity().x = 200.f * player.getFacingRight();
	}
	else if (input == player.getKeyBinding("RUN_LEFT_BUTTON"))
	{
		player.setFacingRight(-1);
		player.getVelocity().x = 200.f * player.getFacingRight();
	}

	return nullptr;
}

void PlayerFallingState::update(Player& player)
{
	if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerFallingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, FALLING_ANIMATION, true);
}
