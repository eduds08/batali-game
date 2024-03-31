#include "PlayerRunningState.h"

#include "PlayerJumpingState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"

#include "Player.h"

PlayerRunningState::PlayerRunningState()
{

}

PlayerRunningState::~PlayerRunningState()
{

}

IPlayerState* PlayerRunningState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if (input == player.JUMP_BUTTON)
	{
		return new PlayerJumpingState();
	}
	else if (input == player.ROLL_BUTTON)
	{
		return new PlayerRollingState();
	}
	else if (input == player.ATTACK_1_BUTTON)
	{
		return new PlayerAttacking1State();
	}
	else if (input == player.ATTACK_2_BUTTON)
	{
		return new PlayerAttacking2State();
	}
	else if (input == player.ULTIMATE_BUTTON)
	{
		return new PlayerUltimateState();
	}

	return nullptr;
}

void PlayerRunningState::update(Player& player)
{
	if (sf::Keyboard::isKeyPressed(player.RUN_RIGHT_BUTTON))
	{
		player.m_facingRight = 1;
		player.getVelocity().x = 200.f * player.m_facingRight;
	}
	else if (sf::Keyboard::isKeyPressed(player.RUN_LEFT_BUTTON))
	{
		player.m_facingRight = -1;
		player.getVelocity().x = 200.f * player.m_facingRight;
	}

	if (player.getVelocity().x == 0.f)
	{
		player.setPlayerState(new PlayerIdleState());
	}
}

void PlayerRunningState::enter(Player& player)
{
	player.getAnimatingComponent()->setNewAnimation(player, RUNNING_ANIMATION, true);
}
