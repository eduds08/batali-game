#include "WindHashashinState.h"

#include "Player.h"

void WindHashashinState::updateAttackHitbox(Player& player, AttackHitbox* attackHitbox)
{
	attackHitbox->reset();

	attackHitbox->setIsUltimateActivate(false);

	if (player.getAnimatingComponent()->getCurrentAnimation()->getName() == "_Attack1")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition());

		if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= WIND_HASHASHIN_ATTACK_1_PT_1_STARTING_FRAME && player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= WIND_HASHASHIN_ATTACK_1_PT_1_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_1_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_1_HEIGHT);
		}
		else if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= WIND_HASHASHIN_ATTACK_1_PT_2_STARTING_FRAME && player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= WIND_HASHASHIN_ATTACK_1_PT_2_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_2_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_2_HEIGHT);
		}

		attackHitbox->setDamage(WIND_HASHASHIN_ATTACK_1_DAMAGE);
	}
	else if (player.getAnimatingComponent()->getCurrentAnimation()->getName() == "_Attack2")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition());

		if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= WIND_HASHASHIN_ATTACK_2_STARTING_FRAME && player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= WIND_HASHASHIN_ATTACK_2_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(WIND_HASHASHIN_ATTACK_2_WIDTH, WIND_HASHASHIN_ATTACK_2_HEIGHT);
			attackHitbox->setDamage(WIND_HASHASHIN_ATTACK_2_DAMAGE);
		}
	}
	else if (player.getAnimatingComponent()->getCurrentAnimation()->getName() == "_AirAttack")
	{
		attackHitbox->setShapePosition(player.getShape().getPosition());

		if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= WIND_HASHASHIN_AIR_ATTACK_STARTING_FRAME && player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= WIND_HASHASHIN_AIR_ATTACK_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(WIND_HASHASHIN_AIR_ATTACK_WIDTH, WIND_HASHASHIN_AIR_ATTACK_HEIGHT);
			attackHitbox->setDamage(WIND_HASHASHIN_AIR_ATTACK_DAMAGE);
		}
	}
	else if (player.getAnimatingComponent()->getCurrentAnimation()->getName() == "_Ultimate")
	{
		attackHitbox->setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);

		if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME && player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME)
		{
			attackHitbox->setShapeSize(player.getShape().getSize());
			attackHitbox->setShapeOrigin(0.f, attackHitbox->getShapeSize().y / 2.f);
			attackHitbox->setShapeScale(static_cast<float>(player.m_facingRight), 1.f);
			attackHitbox->setShapePosition(player.getShape().getPosition() + sf::Vector2f{player.getShape().getSize().x * 2 * (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() - WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME) * static_cast<float>(player.m_facingRight), 0.f});

			attackHitbox->setIsUltimateActivate(true);
		}
		else if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() > WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME && !m_activateUltimate)
		{
			player.setPlayerState(new PlayerIdleState{});
		}
		else if ((player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == WIND_HASHASHIN_ULTIMATE_FIRST_FRAME || player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == WIND_HASHASHIN_ULTIMATE_SECOND_FRAME || player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() == WIND_HASHASHIN_ULTIMATE_THIRD_FRAME) && m_activateUltimate)
		{
			attackHitbox->setShapePosition(player.getShape().getPosition());
			attackHitbox->setShapeSize(player.getShape().getSize());
			attackHitbox->setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);
		}
		else if (player.getAnimatingComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() > WIND_HASHASHIN_ULTIMATE_THIRD_FRAME)
		{
			attackHitbox->setDamage(0);
		}
	}

	attackHitbox->setShapeOrigin(0.f, attackHitbox->getShapeSize().y / 2.f);
	attackHitbox->setShapeScale(static_cast<float>(player.m_facingRight), 1.f);
}

void WindHashashinState::checkIfIsAttacking(Player& enemy, AttackHitbox* attackHitbox)
{
	if (attackHitbox->getShape().getGlobalBounds().intersects(enemy.getShape().getGlobalBounds()))
	{
		if (attackHitbox->getIsUltimateActivate())
		{
			// enemy->teleport to wind_hashashin and sets FastHit
		}
		else
		{
			// enemy->takeDamage
		}
	}
}
