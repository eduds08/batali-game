#include "PlayerAttackComponent.h"

#include "Player.h"
#include "World.h"

void PlayerAttackComponent::update(Player& player, World& world, float& deltaTime)
{
	/*updateAttackHitbox(player);

	for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != player.getId())
		{
			if (enemy->getChosenCharacter()->checkIfIsAttacking(player, enemy->getChosenCharacter()->getAttackHitbox()))
			{
				enemy->getChosenCharacter()->attack(*enemy, player);
			}
		}
	}

	knockbackMove(player, deltaTime);

	player.setKnockbackVelocity(0.f);*/
}

void PlayerAttackComponent::updateAttackHitbox(Player& player)
{
	/*m_attackHitbox.reset();

	const std::string& currentPlayerAnimationName = player.getAnimationComponent()->getCurrentAnimation()->getName();
	const int currentPlayerAnimationFrame = player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex();

	if (currentPlayerAnimationName == "_Attack1")
	{
		updateAttack1(currentPlayerAnimationFrame);
	}
	else if (currentPlayerAnimationName == "_Attack2")
	{
		updateAttack2(currentPlayerAnimationFrame);
	}
	else if (currentPlayerAnimationName == "_AirAttack")
	{
		updateAirAttack(currentPlayerAnimationFrame);
	}
	else if (currentPlayerAnimationName == "_Ultimate")
	{
		updateUltimate(currentPlayerAnimationFrame);
	}
	else
	{
		m_attackHitbox.setDamage(0);
	}

	m_attackHitbox.setShapeOrigin(0.f, m_attackHitbox.getShapeSize().y / 2.f);
	m_attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);*/
}

bool PlayerAttackComponent::isBeingAttackedBy(const AttackHitbox& enemyAttackHitbox, Player& thisPlayer)
{
	if (enemyAttackHitbox.getShape().getGlobalBounds().intersects(thisPlayer.getShape().getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void PlayerAttackComponent::attack(Player& player, Player& enemy)
{
	/*float attackDirection = player.getShape().getPosition().x - enemy.getShape().getPosition().x;

	enemy.setDamageToTake(m_attackHitbox.getDamage());

	enemy.handleCondition("HITTED");

	enemy.setKnockbackVelocity(KNOCKBACK_SPEED * (-attackDirection / abs(attackDirection)));*/
}

void PlayerAttackComponent::knockbackMove(Player& player, float& deltaTime)
{
	/*player.getShape().move(sf::Vector2f{ dynamic_cast<Player*>(&player)->getKnockbackVelocity(), 0.f } *deltaTime);

	player.getSprite().setPosition(sf::Vector2f{ player.getShape().getPosition().x, player.getShape().getPosition().y - (player.getSprite().getTextureRect().getSize().y - player.getShape().getSize().y) / 2.f });*/
}
