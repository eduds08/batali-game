#include "PlayerAttackComponent.h"

#include "Player.h"

PlayerAttackComponent::PlayerAttackComponent()
{
	m_attackHitbox = new AttackHitbox{};
}

PlayerAttackComponent::~PlayerAttackComponent()
{
	if (m_attackHitbox)
	{
		delete m_attackHitbox;
		m_attackHitbox = nullptr;
	}
}

void PlayerAttackComponent::update(GameObject& gameObject, World& world, float& deltaTime)
{
	Player* player = dynamic_cast<Player*>(&gameObject);

	player->getChosenCharacter()->updateAttackHitbox(*player, m_attackHitbox);

	for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != player->getId())
			player->getChosenCharacter()->checkIfIsAttacking(*enemy, m_attackHitbox);
	}
}
