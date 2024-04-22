#include "BoxerState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "ILaunchProjectilesComponent.h"

#include "BoxerUltimateState.h"
#include "World.h"
#include <iostream>

void BoxerState::update(Player& player, World& world, float& deltaTime)
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

void BoxerState::enter(Player& player)
{
	player.setHp(BOXER_HP);
	player.setSpeed(BOXER_SPEED);
	player.setJumpHeight(BOXER_JUMP_HEIGHT);
	player.setRollSpeed(BOXER_ROLL_SPEED);

	player.setSpriteSize(sf::Vector2i{ BOXER_SPRITE_WIDTH, BOXER_SPRITE_HEIGHT });
	player.getShape().setSize(sf::Vector2f{ BOXER_SHAPE_WIDTH, BOXER_SHAPE_HEIGHT });

	player.getSprite().setOrigin(player.getSpriteSize().x / 2.f, player.getSpriteSize().y / 2.f);

	player.getShape().setOrigin(player.getShape().getSize() / 2.f);

	player.getShape().setPosition(LEFT_CHARACTER_FIRST_POSITION);

	player.getShape().setOutlineColor(sf::Color::Red);
	player.getShape().setOutlineThickness(1.f);
}

void BoxerState::updateAttackHitbox(Player& player)
{
	m_attackHitbox.reset();

	const std::string& currentAnimationName = player.getAnimationComponent()->getCurrentAnimation()->getName();
	const int currentAnimationTextureFrameIndex = player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex();

	if (currentAnimationName == "_Attack1")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{ 0.f, -15.f });

		if (currentAnimationTextureFrameIndex >= BOXER_ATTACK_1_STARTING_FRAME && currentAnimationTextureFrameIndex <= BOXER_ATTACK_1_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(BOXER_ATTACK_1_WIDTH, BOXER_ATTACK_1_HEIGHT);
			m_attackHitbox.setDamage(BOXER_ATTACK_1_DAMAGE);
		}
	}
	else if (currentAnimationName == "_Attack2")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{ 16.f * static_cast<float>(player.getFacingRight()), -28.f });

		if (currentAnimationTextureFrameIndex >= BOXER_ATTACK_2_STARTING_FRAME && currentAnimationTextureFrameIndex <= BOXER_ATTACK_2_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(BOXER_ATTACK_2_WIDTH, BOXER_ATTACK_2_HEIGHT);
			m_attackHitbox.setDamage(BOXER_ATTACK_2_DAMAGE);
		}
	}
	else if (currentAnimationName == "_AirAttack")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{ 0.f, -20.f });

		if (currentAnimationTextureFrameIndex >= BOXER_AIR_ATTACK_STARTING_FRAME && currentAnimationTextureFrameIndex <= BOXER_AIR_ATTACK_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(BOXER_AIR_ATTACK_WIDTH, BOXER_AIR_ATTACK_HEIGHT);
			m_attackHitbox.setDamage(BOXER_AIR_ATTACK_DAMAGE);
		}
	}
	else if (currentAnimationName == "_Ultimate")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());
		m_attackHitbox.setDamage(BOXER_ULTIMATE_DAMAGE);

		if (currentAnimationTextureFrameIndex == BOXER_ULTIMATE_PT_1_FRAME)
		{
			if (player.getProjectilesSize() == 0)
			{
				player.launchProjectile(player, std::make_unique<BoxerUltimateState>());
			}
		}
		else if (currentAnimationTextureFrameIndex == BOXER_ULTIMATE_PT_2_FRAME)
		{
			if (player.getProjectilesSize() == 1)
			{
				player.launchProjectile(player, std::make_unique<BoxerUltimateState>());
			}
		}
	}
	else
	{
		m_attackHitbox.setDamage(0);
		/*if (player.getProjectilesSize() == 0)
		{
			m_attackHitbox.setDamage(0);
		}*/
	}

	m_attackHitbox.setShapeOrigin(0.f, m_attackHitbox.getShapeSize().y / 2.f);
	m_attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
}

bool BoxerState::checkIfIsAttacking(Player& player, const AttackHitbox& attackHitbox)
{
	if (attackHitbox.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void BoxerState::attack(Player& player, Player& enemy)
{
	float attackDirection = player.getShape().getPosition().x - enemy.getShape().getPosition().x;

	enemy.setDamageToTake(m_attackHitbox.getDamage());

	enemy.handleCondition("HITTED");

	enemy.setKnockbackVelocity(KNOCKBACK_SPEED * (-attackDirection / abs(attackDirection)));
}

void BoxerState::knockbackMove(Player& player, float& deltaTime)
{
	player.getShape().move(sf::Vector2f{ dynamic_cast<Player*>(&player)->getKnockbackVelocity(), 0.f } *deltaTime);

	player.getSprite().setPosition(sf::Vector2f{ player.getShape().getPosition().x, player.getShape().getPosition().y - (player.getSprite().getTextureRect().getSize().y - player.getShape().getSize().y) / 2.f });
}
