#include "PlayerDeadState.h"

#include "IAnimationComponent.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerDeadState::handleHitted(Player& player, int enemyDamage, float knockbackVelocity)
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
}
