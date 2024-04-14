#include "PlayerDeadState.h"

#include "IAnimationComponent.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerDeadState::handleHitted(Player& player, int enemyDamage, bool fastHit, bool frozen)
{
    return nullptr;
}

std::unique_ptr<IPlayerState> PlayerDeadState::handleInput(Player& player, sf::Keyboard::Scancode input)
{
    return nullptr;
}

void PlayerDeadState::update(Player& player)
{
}

void PlayerDeadState::enter(Player& player)
{
    player.getAnimationComponent()->setNewAnimation(player, DYING_ANIMATION, false);

    player.getShape().setSize(sf::Vector2f{ 0.f, 0.f });
}
