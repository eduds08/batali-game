#include "PlayerAttackingComponent.h"

#include "Player.h"

PlayerAttackingComponent::PlayerAttackingComponent()
{
	m_attackHitbox = new AttackHitbox{};
}

PlayerAttackingComponent::~PlayerAttackingComponent()
{
	delete m_attackHitbox;
	m_attackHitbox = nullptr;
}

void PlayerAttackingComponent::update(Player& player, World& world, float& deltaTime)
{
	player.getChosenCharacter()->updateAttackHitbox(player, m_attackHitbox);

	for (auto& enemy : world.m_players)
	{
		if (enemy->m_playerNumber != player.m_playerNumber)
			player.getChosenCharacter()->checkIfIsAttacking(player, m_attackHitbox);
	}
}
