#include "FireKnightState.h"

#include "IAnimationComponent.h"

#include "Player.h"
#include "World.h"
#include <iostream>

void FireKnightState::update(Player& player, World& world, float& deltaTime)
{
	updateAttackHitbox(player, m_attackHitbox);

	for (auto& enemy : world.m_players)
	{
		if (enemy->getId() != player.getId())
		{
			if (enemy->getChosenCharacter()->checkIfIsAttacking(player, *enemy, enemy->getChosenCharacter()->getAttackHitbox()))
			{
				enemy->getChosenCharacter()->attack(*enemy, player);
			}
		}
	}

	knockbackMove(player, deltaTime);

	player.setKnockbackVelocity(0.f);
}

void FireKnightState::enter(Player& player)
{
	player.setSpriteSize(sf::Vector2i{ FIRE_KNIGHT_SPRITE_WIDTH, FIRE_KNIGHT_SPRITE_HEIGHT });
	player.getShape().setSize(sf::Vector2f{ FIRE_KNIGHT_SHAPE_WIDTH, FIRE_KNIGHT_SHAPE_HEIGHT });

	player.getSprite().setOrigin(player.getSpriteSize().x / 2.f, player.getSpriteSize().y / 2.f);

	player.getShape().setOrigin(player.getShape().getSize() / 2.f);
}

void FireKnightState::updateAttackHitbox(Player& player, AttackHitbox& attackHitbox)
{
	m_attackHitbox.reset();

	if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack1")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_1_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_1_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_1_WIDTH, FIRE_KNIGHT_ATTACK_1_HEIGHT);
			m_attackHitbox.setDamage(FIRE_KNIGHT_ATTACK_1_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack2")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_1_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_1_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_1_HEIGHT);
			m_attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH * static_cast<float>(player.getFacingRight()), 0.f });
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_2_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_2_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_2_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_2_HEIGHT);
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_3_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_3_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_3_HEIGHT);
			m_attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH * static_cast<float>(player.getFacingRight()), 0.f });
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_4_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_4_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_4_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_4_HEIGHT);
		}

		m_attackHitbox.setDamage(FIRE_KNIGHT_ATTACK_2_DAMAGE);
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_AirAttack")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ 0.f, 15.f });

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_AIR_ATTACK_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_AIR_ATTACK_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_AIR_ATTACK_WIDTH, FIRE_KNIGHT_AIR_ATTACK_HEIGHT);
			m_attackHitbox.setDamage(FIRE_KNIGHT_AIR_ATTACK_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Ultimate")
	{
		m_attackHitbox.setShapePosition(player.getShape().getPosition());

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ULTIMATE_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ULTIMATE_ENDING_FRAME)
		{
			m_attackHitbox.setShapeSize(FIRE_KNIGHT_ULTIMATE_WIDTH, FIRE_KNIGHT_ULTIMATE_HEIGHT);
			m_attackHitbox.setDamage(FIRE_KNIGHT_ULTIMATE_DAMAGE);
		}
	}
	else
	{
		m_attackHitbox.setDamage(0);
	}

	m_attackHitbox.setShapeOrigin(0.f, m_attackHitbox.getShapeSize().y / 2.f);
	m_attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
}

bool FireKnightState::checkIfIsAttacking(Player& player, Player& enemy, const AttackHitbox& attackHitbox)
{
	if (attackHitbox.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void FireKnightState::attack(Player& player, Player& enemy)
{
	float attackDirection = player.getShape().getPosition().x - enemy.getShape().getPosition().x;

	enemy.setDamageToTake(m_attackHitbox.getDamage());

	enemy.handleCondition("HITTED");

	enemy.setKnockbackVelocity(KNOCKBACK_SPEED * (-attackDirection / abs(attackDirection)));
}

void FireKnightState::knockbackMove(Player& player, float& deltaTime)
{
	player.getShape().move(sf::Vector2f{ dynamic_cast<Player*>(&player)->getKnockbackVelocity(), 0.f } *deltaTime);

	player.getSprite().setPosition(sf::Vector2f{ player.getShape().getPosition().x, player.getShape().getPosition().y - (player.getSprite().getTextureRect().getSize().y - player.getShape().getSize().y) / 2.f });
}
