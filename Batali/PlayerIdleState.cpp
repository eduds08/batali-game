#include "PlayerIdleState.h"

#include "Player.h"

PlayerIdleState::PlayerIdleState()
{

}

PlayerIdleState::~PlayerIdleState()
{

}

Player* PlayerIdleState::handleInput(Player& player, const std::string& input)
{
	if (input == "RUNNING")
	{
		// return new PlayerRunningState();
	}

	return nullptr;
}

void PlayerIdleState::update(Player& player)
{

}

void PlayerIdleState::enter(Player& player)
{
	// set player new animation
}
