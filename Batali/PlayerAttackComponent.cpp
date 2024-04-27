#include "PlayerAttackComponent.h"

#include "IAnimationComponent.h"
#include "Player.h"
#include "World.h"

void PlayerAttackComponent::update(World& world, float& deltaTime)
{
	updateAttackHitbox();

	for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != m_thisPlayer->getId())
		{
			if (m_thisPlayer->getAttackComponent()->isBeingAttackedBy(enemy->getAttackComponent()->getAttackHitbox()))
			{
				enemy->getAttackComponent()->attack(*m_thisPlayer);
			}
		}
	}

	knockbackMove(deltaTime);

	m_thisPlayer->setKnockbackVelocity(0.f);
}

void PlayerAttackComponent::render(sf::RenderWindow& window)
{
	window.draw(m_attackHitbox.getShape());
}

void PlayerAttackComponent::enter(Player& player)
{
	m_thisPlayer = &player;
}

void PlayerAttackComponent::updateAttackHitbox()
{
	m_attackHitbox.reset();

	const std::string& currentPlayerAnimationName = m_thisPlayer->getAnimationComponent()->getCurrentAnimation()->getName();
	const int currentPlayerAnimationFrame = m_thisPlayer->getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex();

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
	m_attackHitbox.setShapeScale(static_cast<float>(m_thisPlayer->getFacingRight()), 1.f);
}

bool PlayerAttackComponent::isBeingAttackedBy(const AttackHitbox& enemyAttackHitbox)
{
	if (enemyAttackHitbox.getShape().getGlobalBounds().intersects(m_thisPlayer->getShape().getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void PlayerAttackComponent::knockbackMove(float& deltaTime)
{
	m_thisPlayer->getShape().move(sf::Vector2f{ m_thisPlayer->getKnockbackVelocity(), 0.f } *deltaTime);
	m_thisPlayer->getSprite().setPosition(sf::Vector2f{ m_thisPlayer->getShape().getPosition().x, m_thisPlayer->getShape().getPosition().y - (m_thisPlayer->getSprite().getTextureRect().getSize().y - m_thisPlayer->getShape().getSize().y) / 2.f });
}
