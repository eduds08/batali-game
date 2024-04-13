#include "PlayerHittedState.h"

#include "PlayerIdleState.h"

#include "IAnimationComponent.h"
#include "PlayerDeadState.h"
#include "Player.h"

PlayerHittedState::PlayerHittedState(Player& player, Player& enemy)
{
	player.takeDamage(enemy);
}

std::unique_ptr<IPlayerState> PlayerHittedState::handleHitted(Player& player, Player& enemy)
{
	return nullptr;
}

std::unique_ptr<IPlayerState> PlayerHittedState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerHittedState::update(Player& player)
{
	if (player.m_hp <= 0)
	{
		player.setPlayerState(std::make_unique<PlayerDeadState>());
	}

	if (player.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		player.setPlayerState(std::make_unique<PlayerIdleState>());
	}
}

void PlayerHittedState::enter(Player& player)
{
	player.getAnimationComponent()->setNewAnimation(player, HITTED_ANIMATION, false);
}
