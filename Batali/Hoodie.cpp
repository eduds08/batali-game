#include "Hoodie.h"

Hoodie::Hoodie(sf::Vector2f firstPosition)
	: Character{}
{
	m_entityName = "hoodie";

	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = HOODIE_SPRITE_WIDTH;
	m_spriteHeight = HOODIE_SPRITE_HEIGHT;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ HOODIE_SHAPE_WIDTH, HOODIE_SHAPE_HEIGHT });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	//m_attackHitbox.setFillColor(sf::Color{ 255, 0, 0, 50 });
	//m_attackHitbox.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	//m_jumpHeight = HOODIE_JUMP_HEIGHT;
	//m_hp = HOODIE_HP;

	m_speed = HOODIE_SPEED;
	//m_rollSpeed = HOODIE_ROLL_SPEED;
}

void Hoodie::updateAttackHitbox()
{
	m_attackHitboxWidth = 0.f;
	m_attackHitboxHeight = 0.f;

	m_attackHitboxPosition = sf::Vector2f{ -100.f, -100.f };

	if (m_currentTexture == m_entityName + "Attack1")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= HOODIE_ATTACK_1_STARTING_FRAME && m_frameCount <= HOODIE_ATTACK_1_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = HOODIE_ATTACK_1_WIDTH;
			m_attackHitboxHeight = HOODIE_ATTACK_1_HEIGHT;

			m_damage = HOODIE_ATTACK_1_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Attack2")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= HOODIE_ATTACK_2_STARTING_FRAME && m_frameCount <= HOODIE_ATTACK_2_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = HOODIE_ATTACK_2_WIDTH;
			m_attackHitboxHeight = HOODIE_ATTACK_2_HEIGHT;

			m_attackHitboxPosition = getShapePosition();
		}

		m_damage = HOODIE_ATTACK_2_DAMAGE;
	}
	else if (m_currentTexture == m_entityName + "AirAttack")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= HOODIE_AIR_ATTACK_STARTING_FRAME && m_frameCount <= HOODIE_AIR_ATTACK_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = HOODIE_AIR_ATTACK_WIDTH;
			m_attackHitboxHeight = HOODIE_AIR_ATTACK_HEIGHT;

			m_damage = HOODIE_AIR_ATTACK_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Ultimate")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= HOODIE_ULTIMATE_STARTING_FRAME && m_frameCount <= HOODIE_ULTIMATE_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = HOODIE_ULTIMATE_WIDTH;
			m_attackHitboxHeight = HOODIE_ULTIMATE_HEIGHT;

			m_damage = HOODIE_ULTIMATE_DAMAGE;
		}
	}
	else
	{
		m_damage = 0;
	}

	m_attackHitbox.setSize(sf::Vector2f{ m_attackHitboxWidth, m_attackHitboxHeight });
	m_attackHitbox.setOrigin(0.f, m_attackHitboxHeight / 2.f);
	m_attackHitbox.setScale(static_cast<float>(m_facingRight), 1.f);
	m_attackHitbox.setPosition(m_attackHitboxPosition);
}
