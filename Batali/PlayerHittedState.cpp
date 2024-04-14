#include "PlayerHittedState.h"

#include "PlayerIdleState.h"

#include "IAnimationComponent.h"
#include "PlayerDeadState.h"
#include "Player.h"

PlayerHittedState::PlayerHittedState(Player& player, int enemyDamage, bool fastHit, bool frozen)
	: m_fastHit{ fastHit }
	, m_frozen{ frozen }
{
	player.takeDamage(enemyDamage);
}

std::unique_ptr<IPlayerState> PlayerHittedState::handleHitted(Player& player, int enemyDamage, bool fastHit, bool frozen)
{
	return nullptr;
}

std::unique_ptr<IPlayerState> PlayerHittedState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
	return nullptr;
}

void PlayerHittedState::update(Player& player)
{
	if (m_frozen)
	{
		player.setVelocity({ 0.f, 0.f });
	}

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

	player.getAnimationComponent()->setNewAnimation(player, m_fastHit ? FAST_HITTED_ANIMATION : HITTED_ANIMATION, false);
}
