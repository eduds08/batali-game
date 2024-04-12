#include "PlayerAttackComponent.h"

#include "Player.h"

#include "World.h"

PlayerAttackComponent::PlayerAttackComponent()
{
}

PlayerAttackComponent::~PlayerAttackComponent()
{
}

void PlayerAttackComponent::update(GameObject& gameObject, World& world, float& deltaTime)
{
	Player* player = dynamic_cast<Player*>(&gameObject);

	player->getChosenCharacter()->updateAttackHitbox(*player, m_attackHitbox);

	/*for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != player->getId())
			player->getChosenCharacter()->checkIfIsAttacking(*enemy, m_attackHitbox);
	}*/
}
