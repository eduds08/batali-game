#include "FireKnightState.h"

#include "IAnimationComponent.h"

#include "Player.h"

FireKnightState::FireKnightState()
{
}

FireKnightState::~FireKnightState()
{
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
	attackHitbox.reset();

	if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack1")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition());

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_1_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_1_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_1_WIDTH, FIRE_KNIGHT_ATTACK_1_HEIGHT);
			attackHitbox.setDamage(FIRE_KNIGHT_ATTACK_1_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Attack2")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition());

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_1_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_1_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_1_HEIGHT);
			attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH * static_cast<float>(player.getFacingRight()), 0.f });
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_2_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_2_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_2_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_2_HEIGHT);
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_3_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_3_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_3_HEIGHT);
			attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH * static_cast<float>(player.getFacingRight()), 0.f });
		}
		else if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ATTACK_2_PT_4_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ATTACK_2_PT_4_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_4_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_4_HEIGHT);
		}

		attackHitbox.setDamage(FIRE_KNIGHT_ATTACK_2_DAMAGE);
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_AirAttack")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ 0.f, 15.f });

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_AIR_ATTACK_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_AIR_ATTACK_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_AIR_ATTACK_WIDTH, FIRE_KNIGHT_AIR_ATTACK_HEIGHT);
			attackHitbox.setDamage(FIRE_KNIGHT_AIR_ATTACK_DAMAGE);
		}
	}
	else if (player.getAnimationComponent()->getCurrentAnimation()->getName() == "_Ultimate")
	{
		attackHitbox.setShapePosition(player.getShape().getPosition());

		if (player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() >= FIRE_KNIGHT_ULTIMATE_STARTING_FRAME && player.getAnimationComponent()->getCurrentAnimation()->getCurrentTextureFrameIndex() <= FIRE_KNIGHT_ULTIMATE_ENDING_FRAME)
		{
			attackHitbox.setShapeSize(FIRE_KNIGHT_ULTIMATE_WIDTH, FIRE_KNIGHT_ULTIMATE_HEIGHT);
			attackHitbox.setDamage(FIRE_KNIGHT_ULTIMATE_DAMAGE);
		}
	}
	else
	{
		attackHitbox.setDamage(0);
	}

	attackHitbox.setShapeOrigin(0.f, attackHitbox.getShapeSize().y / 2.f);
	attackHitbox.setShapeScale(static_cast<float>(player.getFacingRight()), 1.f);
}

void FireKnightState::checkIfIsAttacking(Player& enemy, AttackHitbox& attackHitbox)
{
	if (attackHitbox.getShape().getGlobalBounds().intersects(enemy.getShape().getGlobalBounds()))
	{
		// enemy->takeDamage()
	}
}
