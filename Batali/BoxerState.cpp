#include "BoxerState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "ILaunchProjectilesComponent.h"

#include "BoxerUltimateState.h"

#include <iostream>

void BoxerState::enter(Player& player)
{
	player.setSpriteSize(sf::Vector2i{ BOXER_SPRITE_WIDTH, BOXER_SPRITE_HEIGHT });
	player.getShape().setSize(sf::Vector2f{ BOXER_SHAPE_WIDTH, BOXER_SHAPE_HEIGHT });

	player.getSprite().setOrigin(player.getSpriteSize().x / 2.f, player.getSpriteSize().y / 2.f);

	player.getShape().setOrigin(player.getShape().getSize() / 2.f);
}

void BoxerState::updateAttackHitbox(Player& player, AttackHitbox& attackHitbox)
{
	attackHitbox.reset();

	if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack1")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{0.f, -15.f});

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= BOXER_ATTACK_1_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= BOXER_ATTACK_1_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(BOXER_ATTACK_1_WIDTH, BOXER_ATTACK_1_HEIGHT);
			attackHitbox.setDamage(BOXER_ATTACK_1_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack2")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{16.f * static_cast<float>(player.getFacingRight()), -28.f});

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= BOXER_ATTACK_2_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= BOXER_ATTACK_2_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(BOXER_ATTACK_2_WIDTH, BOXER_ATTACK_2_HEIGHT);
			attackHitbox.setDamage(BOXER_ATTACK_2_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_AirAttack")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition() + sf::Vector2f{0.f, -20.f});

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= BOXER_AIR_ATTACK_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= BOXER_AIR_ATTACK_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(BOXER_AIR_ATTACK_WIDTH, BOXER_AIR_ATTACK_HEIGHT);
			attackHitbox.setDamage(BOXER_AIR_ATTACK_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Ultimate")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition());
		attackHitbox.setDamage(BOXER_ULTIMATE_DAMAGE);

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == BOXER_ULTIMATE_PT_1_FRAME)
		{
			if (player.getLaunchProjectilesComponent()->getProjectiles().size() == 0)
			{
				player.getLaunchProjectilesComponent()->launchProjectile(player, std::make_unique<BoxerUltimateState>());
			}
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == BOXER_ULTIMATE_PT_2_FRAME)
		{
			if (player.getLaunchProjectilesComponent()->getProjectiles().size() == 1)
			{
				player.getLaunchProjectilesComponent()->launchProjectile(player, std::make_unique<BoxerUltimateState>());
			}
		}
	}
	else
	{
		if (player.getLaunchProjectilesComponent()->getProjectiles().size() == 0)
		{
			attackHitbox.setDamage(0);
		}
	}

	attackHitbox.setShapeOrigin(0.f, attackHitbox.getShapeSize().y / 2.f);
	attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
}

void BoxerState::checkIfIsAttacking(Player& enemy, AttackHitbox& attackHitbox)
{
	if (attackHitbox.getShape().getGlobalBounds().intersects(enemy.getShape().getGlobalBounds()))
	{
		//enemy.handleCondition("HITTED");
	}
}
