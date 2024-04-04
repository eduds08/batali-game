#include "PlayerIdleState.h"

#include "Player.h"

#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerRollingState.h"
#include "PlayerAttacking1State.h"
#include "PlayerAttacking2State.h"
#include "PlayerUltimateState.h"
#include "IAnimationComponent.h"
#include "Player.h"

PlayerIdleState::PlayerIdleState()
{

}

PlayerIdleState::~PlayerIdleState()
{

}

std::shared_ptr<IPlayerState> PlayerIdleState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	if (input == player.getKeyBinding("JUMP_BUTTON"))
	{
		return std::make_shared<PlayerJumpingState>();
	}
	else if (input == player.getKeyBinding("RUN_RIGHT_BUTTON"))
	{
		player.setFacingRight(1);
		return std::make_shared<PlayerRunningState>();
	}
	else if (input == player.getKeyBinding("RUN_LEFT_BUTTON"))
	{
		player.setFacingRight(-1);
		return std::make_shared<PlayerRunningState>();
	}
	else if (input == player.getKeyBinding("ROLL_BUTTON"))
	{
		return std::make_shared<PlayerRollingState>();
	}
	else if (input == player.getKeyBinding("ATTACK_1_BUTTON"))
	{
		return std::make_shared<PlayerAttacking1State>();
	}
	else if (input == player.getKeyBinding("ATTACK_2_BUTTON"))
	{
		return std::make_shared<PlayerAttacking2State>();
	}
	else if (input == player.getKeyBinding("ULTIMATE_BUTTON"))
	{
		return std::make_shared<PlayerUltimateState>();
	}

	return nullptr;
}

void PlayerIdleState::update(Player& player)
{

}

void PlayerIdleState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, IDLE_ANIMATION, true);
}
