#include "FireKnightAttackComponent.h"

FireKnightAttackComponent::FireKnightAttackComponent()
	: PlayerAttackComponent{}
{
}

void FireKnightAttackComponent::updateAttack1(const int currentPlayerAnimationFrame)
{
	/*m_attackHitbox.setShapePosition(player.getShape().getPosition());

	if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_ATTACK_1_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_ATTACK_1_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_1_WIDTH, FIRE_KNIGHT_ATTACK_1_HEIGHT);
		m_attackHitbox.setDamage(FIRE_KNIGHT_ATTACK_1_DAMAGE);
	}*/
}

void FireKnightAttackComponent::updateAttack2(const int currentPlayerAnimationFrame)
{
	/*m_attackHitbox.setShapePosition(player.getShape().getPosition());

	if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_ATTACK_2_PT_1_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_ATTACK_2_PT_1_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_1_HEIGHT);
		m_attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH * static_cast<float>(player.getFacingRight()), 0.f });
	}
	else if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_ATTACK_2_PT_2_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_ATTACK_2_PT_2_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_2_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_2_HEIGHT);
	}
	else if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_ATTACK_2_PT_3_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_ATTACK_2_PT_3_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_3_HEIGHT);
		m_attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH * static_cast<float>(player.getFacingRight()), 0.f });
	}
	else if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_ATTACK_2_PT_4_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_ATTACK_2_PT_4_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_ATTACK_2_PT_4_WIDTH, FIRE_KNIGHT_ATTACK_2_PT_4_HEIGHT);
	}

	m_attackHitbox.setDamage(FIRE_KNIGHT_ATTACK_2_DAMAGE);*/
}

void FireKnightAttackComponent::updateAirAttack(const int currentPlayerAnimationFrame)
{
	/*m_attackHitbox.setShapePosition(player.getShape().getPosition() - sf::Vector2f{ 0.f, 15.f });

	if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_AIR_ATTACK_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_AIR_ATTACK_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_AIR_ATTACK_WIDTH, FIRE_KNIGHT_AIR_ATTACK_HEIGHT);
		m_attackHitbox.setDamage(FIRE_KNIGHT_AIR_ATTACK_DAMAGE);
	}*/
}

void FireKnightAttackComponent::updateUltimate(const int currentPlayerAnimationFrame)
{
	/*m_attackHitbox.setShapePosition(player.getShape().getPosition());

	if (currentAnimationTextureFrameIndex >= FIRE_KNIGHT_ULTIMATE_STARTING_FRAME && currentAnimationTextureFrameIndex <= FIRE_KNIGHT_ULTIMATE_ENDING_FRAME)
	{
		m_attackHitbox.setShapeSize(FIRE_KNIGHT_ULTIMATE_WIDTH, FIRE_KNIGHT_ULTIMATE_HEIGHT);
		m_attackHitbox.setDamage(FIRE_KNIGHT_ULTIMATE_DAMAGE);
	}*/
}
