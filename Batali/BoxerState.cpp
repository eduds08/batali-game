#include "BoxerState.h"
#include "IAnimationComponent.h"
#include "Player.h"
#include "ILaunchProjectilesComponent.h"

#include "BoxerUltimateState.h"

void BoxerState::updateAttackHitbox(Player& player, AttackHitbox* attackHitbox)
{
	attackHitbox->reset();

	if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack1")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition() + sf::Vector2f{0.f, -15.f});

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= BOXER_ATTACK_1_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= BOXER_ATTACK_1_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(BOXER_ATTACK_1_WIDTH, BOXER_ATTACK_1_HEIGHT);
			attackHitbox->setDamage(BOXER_ATTACK_1_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack2")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition() + sf::Vector2f{16.f * static_cast<float>(player.getFacingRight()), -28.f});

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= BOXER_ATTACK_2_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= BOXER_ATTACK_2_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(BOXER_ATTACK_2_WIDTH, BOXER_ATTACK_2_HEIGHT);
			attackHitbox->setDamage(BOXER_ATTACK_2_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_AirAttack")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition() + sf::Vector2f{0.f, -20.f});

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= BOXER_AIR_ATTACK_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= BOXER_AIR_ATTACK_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(BOXER_AIR_ATTACK_WIDTH, BOXER_AIR_ATTACK_HEIGHT);
			attackHitbox->setDamage(BOXER_AIR_ATTACK_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Ultimate")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition());
		attackHitbox->setDamage(BOXER_ULTIMATE_DAMAGE);

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == BOXER_ULTIMATE_PT_1_FRAME)
		{
			if (player.getLaunchProjectilesComponent()->getProjectiles().size() == 0)
			{
				player.getLaunchProjectilesComponent()->launchProjectile(player, new BoxerUltimateState{});
			}
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == BOXER_ULTIMATE_PT_2_FRAME)
		{
			if (player.getLaunchProjectilesComponent()->getProjectiles().size() == 1)
			{
				player.getLaunchProjectilesComponent()->launchProjectile(player, new BoxerUltimateState{});
			}
		}
	}
	else
	{
		if (player.getLaunchProjectilesComponent()->getProjectiles().size() == 0)
		{
			attackHitbox->setDamage(0);
		}
	}

	attackHitbox->setShapeOrigin(0.f, attackHitbox->getShapeSize().y / 2.f);
	attackHitbox->setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
}

void BoxerState::checkIfIsAttacking(Player& enemy, AttackHitbox* attackHitbox)
{
	if (attackHitbox->getShape().getGlobalBounds().intersects(enemy.getShape().getGlobalBounds()))
	{
		// enemy->takeDamage()
	}
}
