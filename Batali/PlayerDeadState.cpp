#include "PlayerDeadState.h"

#include "IAnimationComponent.h"

#include "Player.h"

std::unique_ptr<IPlayerState> PlayerDeadState::handleCondition(Player& player, const std::string& condition)
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
