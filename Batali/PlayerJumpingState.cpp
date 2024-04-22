#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include "PlayerIdleState.h"
#include "PlayerAirAttackingState.h"
#include "PlayerHittedState.h"
#include "IAnimationComponent.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerJumpingState::handleCondition(Player& player, const std::string& condition)
{
	if ((condition == "ATTACK_1_BUTTON" || condition == "ATTACK_2_BUTTON"))
	{
		return std::make_unique<PlayerAirAttackingState>();
	}
	else if (condition == "RUN_RIGHT_BUTTON")
	{
		player.setFacingRight(1);
		player.getVelocity().x = player.getSpeed() * player.getFacingRight();
	}
	else if (condition == "RUN_LEFT_BUTTON")
	{
		player.setFacingRight(-1);
		player.getVelocity().x = player.getSpeed() * player.getFacingRight();
	}
	else if (condition == "HITTED")
	{
		return std::make_unique<PlayerHittedState>();
	}

	return nullptr;
}

void PlayerJumpingState::update(Player& player)
{
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
	player.getVelocity().y = -1 * sqrt(2.f * GRAVITY * player.getJumpHeight());

	player.getAnimationComponent()->setNewAnimation(player, JUMPING_ANIMATION, true);
}
