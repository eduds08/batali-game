#include "PlayerHittedState.h"

#include "PlayerIdleState.h"

#include "IAnimationComponent.h"

#include "Player.h"

PlayerHittedState::PlayerHittedState()
{

}

std::unique_ptr<IPlayerState> PlayerHittedState::handleCondition(Player& player, const std::string& condition)
{
	return nullptr;
}

std::unique_ptr<IPlayerState> PlayerHittedState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerHittedState::update(Player& player)
{
	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerHittedState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, HITTED_ANIMATION, false);

	player.takeDamage();
}
