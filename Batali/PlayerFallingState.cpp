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

std::unique_ptr<IPlayerState> PlayerFallingState::handleHitted(Player& player, int enemyDamage, bool fastHit, bool frozen)
{
	return std::make_unique<PlayerHittedState>(player, enemyDamage, fastHit, frozen);
}

std::unique_ptr<IPlayerState> PlayerFallingState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerFallingState::update(Player& player)
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

	if (player.getVelocity().y == 0.f)
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerFallingState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, FALLING_ANIMATION, true);
}
