#include "WindHashashinState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "World.h"

#include <iostream>

void WindHashashinState::update(Player& player, World& world, float& deltaTime)
{
	updateAttackHitbox(player);

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

	player.setKnockbackVelocity(0.f);
}

void WindHashashinState::enter(Player& player)
{
	player.setHp(WIND_HASHASHIN_HP);
	player.setSpeed(WIND_HASHASHIN_SPEED);
	player.setJumpHeight(WIND_HASHASHIN_JUMP_HEIGHT);
	player.setRollSpeed(WIND_HASHASHIN_ROLL_SPEED);

	player.setSpriteSize(sf::Vector2i{ WIND_HASHASHIN_SPRITE_WIDTH, WIND_HASHASHIN_SPRITE_HEIGHT });
	player.getShape().setSize(sf::Vector2f{ WIND_HASHASHIN_SHAPE_WIDTH, WIND_HASHASHIN_SHAPE_HEIGHT });

	player.getSprite().setOrigin(player.getSpriteSize().x / 2.f, player.getSpriteSize().y / 2.f);

	player.getShape().setOrigin(player.getShape().getSize() / 2.f);

	player.getShape().setPosition(LEFT_CHARACTER_FIRST_POSITION);

	player.getShape().setOutlineColor(sf::Color::Red);
	player.getShape().setOutlineThickness(1.f);
}

void WindHashashinState::updateAttackHitbox(Player& player)
{
	m_attackHitbox.reset();

	const std::string& currentAnimationName = player.getAnimationComponent()->getCurrentAnimation()->getName();
	const int currentAnimationTextureFrameIndex = player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex();

	m_attackHitbox.setIsUltimateActivate(false);

	if (currentAnimationName == "_Attack1")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());

		if (currentAnimationTextureFrameIndex >= WIND_HASHASHIN_ATTACK_1_PT_1_STARTING_FRAME && currentAnimationTextureFrameIndex <= WIND_HASHASHIN_ATTACK_1_PT_1_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_1_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_1_HEIGHT);
		}
		else if (currentAnimationTextureFrameIndex >= WIND_HASHASHIN_ATTACK_1_PT_2_STARTING_FRAME && currentAnimationTextureFrameIndex <= WIND_HASHASHIN_ATTACK_1_PT_2_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_2_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_2_HEIGHT);
		}

		m_attackHitbox.setDamage(WIND_HASHASHIN_ATTACK_1_DAMAGE);
	}
	else if (currentAnimationName == "_Attack2")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());

		if (currentAnimationTextureFrameIndex >= WIND_HASHASHIN_ATTACK_2_STARTING_FRAME && currentAnimationTextureFrameIndex <= WIND_HASHASHIN_ATTACK_2_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(WIND_HASHASHIN_ATTACK_2_WIDTH, WIND_HASHASHIN_ATTACK_2_HEIGHT);
			m_attackHitbox.setDamage(WIND_HASHASHIN_ATTACK_2_DAMAGE);
		}
	}
	else if (currentAnimationName == "_AirAttack")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());

		if (currentAnimationTextureFrameIndex >= WIND_HASHASHIN_AIR_ATTACK_STARTING_FRAME && currentAnimationTextureFrameIndex <= WIND_HASHASHIN_AIR_ATTACK_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(WIND_HASHASHIN_AIR_ATTACK_WIDTH, WIND_HASHASHIN_AIR_ATTACK_HEIGHT);
			m_attackHitbox.setDamage(WIND_HASHASHIN_AIR_ATTACK_DAMAGE);
		}
	}
	else if (currentAnimationName == "_Ultimate")
	{
		m_attackHitbox.setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);

		m_attackHitbox.setIsUltimateActivate(false);

		if (currentAnimationTextureFrameIndex >= WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME && currentAnimationTextureFrameIndex <= WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(player.getShape().getSize());
			m_attackHitbox.setShapeOrigin(0.f, m_attackHitbox.getShapeSize().y / 2.f);
			m_attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
			m_attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{ player.getShape().getSize().x * 2 * (currentAnimationTextureFrameIndex - WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME) * static_cast<float>(player.getFacingRight()), 0.f });

			m_attackHitbox.setIsUltimateActivate(true);
		}
		else if (currentAnimationTextureFrameIndex > WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME && !m_activateUltimate)
		{
			player.setPlayerState(std::make_unique<PlayerIdleState>());
		}
		else if ((currentAnimationTextureFrameIndex == WIND_HASHASHIN_ULTIMATE_FIRST_FRAME || currentAnimationTextureFrameIndex == WIND_HASHASHIN_ULTIMATE_SECOND_FRAME || currentAnimationTextureFrameIndex == WIND_HASHASHIN_ULTIMATE_THIRD_FRAME) && m_activateUltimate)
		{
			m_attackHitbox.setShapePosition(player.getShape().getPosition());
			m_attackHitbox.setShapeSize(player.getShape().getSize());
			m_attackHitbox.setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);
		}
		else if (currentAnimationTextureFrameIndex > WIND_HASHASHIN_ULTIMATE_THIRD_FRAME)
		{
			m_attackHitbox.setDamage(0);
		}
	}
	else
	{
		m_activateUltimate = false;
	}

	m_attackHitbox.setShapeOrigin(0.f, m_attackHitbox.getShapeSize().y / 2.f);
	m_attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
}

bool WindHashashinState::checkIfIsAttacking(Player& player, const AttackHitbox& attackHitbox)
{
	if (attackHitbox.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void WindHashashinState::attack(Player& player, Player& enemy)
{
	if (m_attackHitbox.getIsUltimateActivate())
	{
		enemy.getShape().setPosition(player.getShape().getPosition());
		enemy.getSprite().setPosition(enemy.getShape().getPosition() + sf::Vector2f{ 0.f, -(enemy.getSprite().getTextureRect().getSize().y - enemy.getShape().getSize().y) / 2.f });
		m_activateUltimate = true;
	}
	else
	{
		float attackDirection = player.getShape().getPosition().x - enemy.getShape().getPosition().x;
		enemy.setDamageToTake(m_attackHitbox.getDamage());
		enemy.handleCondition("HITTED");
		float knockbackVelocity = attackDirection != 0.f ? KNOCKBACK_SPEED * (-attackDirection / abs(attackDirection)) : 0.f;
		enemy.setKnockbackVelocity(knockbackVelocity);
	}
}

void WindHashashinState::knockbackMove(Player& player, float& deltaTime)
{
	player.getShape().move(sf::Vector2f{ dynamic_cast<Player*>(&player)->getKnockbackVelocity(), 0.f } *deltaTime);

	player.getSprite().setPosition(sf::Vector2f{ player.getShape().getPosition().x, player.getShape().getPosition().y - (player.getSprite().getTextureRect().getSize().y - player.getShape().getSize().y) / 2.f });
}
