#include "WindHashashin.h"

#include "AttackingState.h"
#include "FallingState.h"
#include "IdleState.h"

WindHashashin::WindHashashin(sf::Vector2f firstPosition)
	: Character{}
{
	m_actorName = "wind_hashashin";
	m_state = new FallingState{};
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = WIND_HASHASHIN_SPRITE_WIDTH;
	m_spriteHeight = WIND_HASHASHIN_SPRITE_HEIGHT;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	//changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);
	m_state->enter(*this);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ WIND_HASHASHIN_SHAPE_WIDTH, WIND_HASHASHIN_SHAPE_HEIGHT});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	//m_jumpHeight = WIND_HASHASHIN_JUMP_HEIGHT;
	//m_hp = WIND_HASHASHIN_HP;

	m_speed = WIND_HASHASHIN_SPEED;
	//m_rollSpeed = WIND_HASHASHIN_ROLL_SPEED;
}

void WindHashashin::updateAttackHitbox(AttackHitbox* m_attackHitbox)
{
	m_attackHitbox->reset();

	m_attackHitbox->setIsUltimateActivate(false);

	if (m_currentTexture == m_actorName + "Attack1")
	{
		m_attackHitbox->setShapePosition(getShapePosition());

		if (m_frameCount >= WIND_HASHASHIN_ATTACK_1_PT_1_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ATTACK_1_PT_1_ENDING_FRAME)
		{
			m_attackHitbox->setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_1_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_1_HEIGHT);
		}
		else if (m_frameCount >= WIND_HASHASHIN_ATTACK_1_PT_2_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ATTACK_1_PT_2_ENDING_FRAME)
		{
			m_attackHitbox->setShapeSize(WIND_HASHASHIN_ATTACK_1_PT_2_WIDTH, WIND_HASHASHIN_ATTACK_1_PT_2_HEIGHT);
		}

		m_attackHitbox->setDamage(WIND_HASHASHIN_ATTACK_1_DAMAGE);
	}
	else if (m_currentTexture == m_actorName + "Attack2")
	{
		m_attackHitbox->setShapePosition(getShapePosition());

		if (m_frameCount >= WIND_HASHASHIN_ATTACK_2_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ATTACK_2_ENDING_FRAME)
		{
			m_attackHitbox->setShapeSize(WIND_HASHASHIN_ATTACK_2_WIDTH, WIND_HASHASHIN_ATTACK_2_HEIGHT);
			m_attackHitbox->setDamage(WIND_HASHASHIN_ATTACK_2_DAMAGE);
		}
	}
	else if (m_currentTexture == m_actorName + "AirAttack")
	{
		m_attackHitbox->setShapePosition(getShapePosition());

		if (m_frameCount >= WIND_HASHASHIN_AIR_ATTACK_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_AIR_ATTACK_ENDING_FRAME)
		{
			m_attackHitbox->setShapeSize(WIND_HASHASHIN_AIR_ATTACK_WIDTH, WIND_HASHASHIN_AIR_ATTACK_HEIGHT);
			m_attackHitbox->setDamage(WIND_HASHASHIN_AIR_ATTACK_DAMAGE);
		}
	}
	else if (m_currentTexture == m_actorName + "Ultimate")
	{
		m_attackHitbox->setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);

		if (m_frameCount >= WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME)
		{
			m_attackHitbox->setShapeSize(getShapeSize());
			m_attackHitbox->setShapeOrigin(0.f, m_attackHitbox->getShapeSize().y / 2.f);
			m_attackHitbox->setShapeScale(static_cast<float>(m_facingRight), 1.f);
			m_attackHitbox->setShapePosition(getShapePosition() + sf::Vector2f{getShapeSize().x * 2 * (m_frameCount - WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME) * m_facingRight, 0.f});

			m_attackHitbox->setIsUltimateActivate(true);
		}
		else if (m_frameCount > WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME && !m_activateUltimate)
		{
			setState(new IdleState{});
		}
		else if ((m_frameCount == WIND_HASHASHIN_ULTIMATE_FIRST_FRAME || m_frameCount == WIND_HASHASHIN_ULTIMATE_SECOND_FRAME || m_frameCount == WIND_HASHASHIN_ULTIMATE_THIRD_FRAME) && m_activateUltimate)
		{
			m_attackHitbox->setShapePosition(getShapePosition());
			m_attackHitbox->setShapeSize(getShapeSize());
			m_attackHitbox->setDamage(WIND_HASHASHIN_ULTIMATE_DAMAGE);
		}
		else if (m_frameCount > WIND_HASHASHIN_ULTIMATE_THIRD_FRAME)
		{
			m_attackHitbox->setDamage(0);
		}
	}

	m_attackHitbox->setShapeOrigin(0.f, m_attackHitbox->getShapeSize().y / 2.f);
	m_attackHitbox->setShapeScale(static_cast<float>(m_facingRight), 1.f);
}
