#include "WindHashasinAttackComponent.h"

#include "PlayerIdleState.h"
#include "IAnimationComponent.h"
#include "Player.h"

void WindHashasinAttackComponent::updateAttack1(const int currentPlayerAnimationFrame)
{
	m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition());

	if (currentPlayerAnimationFrame >= WIND_HASHASHIN_ATTACK_1_PT_1_STARTING_FRAME && currentPlayerAnimationFrame <= WIND_HASHASHIN_ATTACK_1_PT_1_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_1_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_1_HEIGHT);
	}
	else if (currentPlayerAnimationFrame >= WIND_HASHASHIN_ATTACK_1_PT_2_STARTING_FRAME && currentPlayerAnimationFrame <= WIND_HASHASHIN_ATTACK_1_PT_2_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_2_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_2_HEIGHT);
	}

	m_attackHitbox.setDamage(WIND_HASHASHIN_ATTACK_1_DAMAGE);
}

void WindHashasinAttackComponent::updateAttack2(const int currentPlayerAnimationFrame)
{
	m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition());

	if (currentPlayerAnimationFrame >= WIND_HASHASHIN_ATTACK_2_STARTING_FRAME && currentPlayerAnimationFrame <= WIND_HASHASHIN_ATTACK_2_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(WIND_HASHASHIN_ATTACK_2_WIDTH, WIND_HASHASHIN_ATTACK_2_HEIGHT);
		m_attackHitbox.setDamage(WIND_HASHASHIN_ATTACK_2_DAMAGE);
	}
}

void WindHashasinAttackComponent::updateAirAttack(const int currentPlayerAnimationFrame)
{
	m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition());

	if (currentPlayerAnimationFrame >= WIND_HASHASHIN_AIR_ATTACK_STARTING_FRAME && currentPlayerAnimationFrame <= WIND_HASHASHIN_AIR_ATTACK_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(WIND_HASHASHIN_AIR_ATTACK_WIDTH, WIND_HASHASHIN_AIR_ATTACK_HEIGHT);
		m_attackHitbox.setDamage(WIND_HASHASHIN_AIR_ATTACK_DAMAGE);
	}
}

void WindHashasinAttackComponent::updateUltimate(const int currentPlayerAnimationFrame)
{
	if (currentPlayerAnimationFrame >= WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME && currentPlayerAnimationFrame <= WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(m_thisPlayer->getShape().getSize());
		m_attackHitbox.setShapeOrigin(0.f, m_attackHitbox.getShapeSize().y / 2.f);
		m_attackHitbox.setShapeScale(static_cast<float>(m_thisPlayer->getFacingRight()), 1.f);
		m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition() + sf::Vector2f{ m_thisPlayer->getShape().getSize().x * 2 * (currentPlayerAnimationFrame - WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME) * static_cast<float>(m_thisPlayer->getFacingRight()), 0.f });

		m_attackHitbox.setIsUltimateActivate(true);
	}
	else if (currentPlayerAnimationFrame > WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME && !m_activeUltimate)
	{
		m_thisPlayer->setPlayerState(std::make_unique<PlayerIdleState>());
	}
	else if ((currentPlayerAnimationFrame == WIND_HASHASHIN_ULTIMATE_FIRST_FRAME || currentPlayerAnimationFrame == WIND_HASHASHIN_ULTIMATE_SECOND_FRAME || currentPlayerAnimationFrame == WIND_HASHASHIN_ULTIMATE_THIRD_FRAME) && m_activeUltimate)
	{
		m_attackHitbox.setShapePosition(m_thisPlayer->getShape().getPosition());
		m_attackHitbox.setShapeSize(m_thisPlayer->getShape().getSize());
		m_attackHitbox.setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);
	}
}

void WindHashasinAttackComponent::updateAttackHitbox()
{
	m_attackHitbox.setIsUltimateActivate(false);
	
	PlayerAttackComponent::updateAttackHitbox();
}

void WindHashasinAttackComponent::attack(Player& enemy)
{
	if (m_attackHitbox.getIsUltimateActivate())
	{
		enemy.getShape().setPosition(m_thisPlayer->getShape().getPosition());
		enemy.getSprite().setPosition(enemy.getShape().getPosition() + sf::Vector2f{ 0.f, -(enemy.getSprite().getTextureRect().getSize().y - enemy.getShape().getSize().y) / 2.f });
		m_activeUltimate = true;
	}
	else
	{
		float attackDirection = m_thisPlayer->getShape().getPosition().x - enemy.getShape().getPosition().x;
		float knockbackVelocity = attackDirection != 0.f ? KNOCKBACK_SPEED * (-attackDirection / abs(attackDirection)) : 0.f;
		enemy.setKnockbackVelocity(knockbackVelocity);
		enemy.setDamageToTake(m_attackHitbox.getDamage());
		enemy.handleCondition("HITTED");
	}
}
