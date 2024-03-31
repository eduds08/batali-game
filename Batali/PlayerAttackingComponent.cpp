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

void PlayerAttackingComponent::update(Player& player, float& deltaTime)
{
	//character.updateAttackHitbox(m_attackHitbox);
	player.getChosenCharacter()->updateAttackHitbox(player, m_attackHitbox);
}
