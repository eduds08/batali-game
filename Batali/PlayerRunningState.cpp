#include "PlayerRunningState.h"

#include "PlayerJumpingState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"
#include "PlayerIdleState.h"
#include "PlayerHittedState.h"

#include "IAnimationComponent.h"
#include "Player.h"

PlayerRunningState::PlayerRunningState()
{

}

PlayerRunningState::~PlayerRunningState()
{

}

std::unique_ptr<IPlayerState> PlayerRunningState::handleHitted(Player& player, int enemyDamage, float knockbackVelocity, bool fastHit, bool frozen)
{
	return std::make_unique<PlayerHittedState>(player, enemyDamage, knockbackVelocity, fastHit, frozen);
}

std::unique_ptr<IPlayerState> PlayerRunningState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if (input == player.getKeyBinding("JUMP_BUTTON"))
	{
		return std::make_unique<PlayerJumpingState>();
	}
	else if (input == player.getKeyBinding("ROLL_BUTTON"))
	{
		return std::make_unique<PlayerRollingState>();
	}
	else if (input == player.getKeyBinding("ATTACK_1_BUTTON"))
	{
		return std::make_unique<PlayerAttacking1State>();
	}
	else if (input == player.getKeyBinding("ATTACK_2_BUTTON"))
	{
		return std::make_unique<PlayerAttacking2State>();
	}
	else if (input == player.getKeyBinding("ULTIMATE_BUTTON"))
	{
		return std::make_unique<PlayerUltimateState>();
	}
	else if (input == player.getKeyBinding("RUN_RIGHT_BUTTON"))
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

void PlayerRunningState::update(Player& player)
{
	if (player.getVelocity().x == 0.f)
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerRunningState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, RUNNING_ANIMATION, true);
	player.getVelocity().x = 1.f;
}
