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

	for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != player->getId())
			player->getChosenCharacter()->checkIfIsAttacking(*player, *enemy, m_attackHitbox);
	}

	if (player->m_hp <= 0)
	{
		player->m_knockbackVelocity = 0.f;
	}

	knockbackMove(gameObject, deltaTime);

	player->m_knockbackVelocity = 0.f;
}

void PlayerAttackComponent::knockbackMove(GameObject& gameObject, float& deltaTime)
{
	gameObject.getShape().move(sf::Vector2f{ dynamic_cast<Player*>(&gameObject)->m_knockbackVelocity, 0.f } *deltaTime);

	gameObject.getSprite().setPosition(sf::Vector2f{ gameObject.getShape().getPosition().x, gameObject.getShape().getPosition().y - (gameObject.getSprite().getTextureRect().getSize().y - gameObject.getShape().getSize().y) / 2.f });
}
