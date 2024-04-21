#include "HoodieState.h"

#include "Player.h"

void HoodieState::update(Player& player, World& world, float& deltaTime)
{
}

void HoodieState::enter(Player& player)
{
}

void HoodieState::updateAttackHitbox(Player& player, AttackHitbox& attackHitbox)
{
}

bool HoodieState::checkIfIsAttacking(Player& player, Player& enemy, const AttackHitbox& attackHitbox)
{
	return false;
}
