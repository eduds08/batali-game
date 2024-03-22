#include "FireKnight.h"


#include "FallingState.h"

FireKnight::FireKnight(sf::Vector2f firstPosition)
	: Character{}
{
	m_entityName = "fire_knight";

	m_state = new FallingState{};

	

	initTexturesMap();

	

	// Initialize sprite
	m_spriteWidth = FIRE_KNIGHT_SPRITE_WIDTH;
	m_spriteHeight = FIRE_KNIGHT_SPRITE_HEIGHT;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	//changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);
	m_state->enter(*this);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ FIRE_KNIGHT_SHAPE_WIDTH, FIRE_KNIGHT_SHAPE_HEIGHT});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_attackHitbox.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	//m_jumpHeight = FIRE_KNIGHT_JUMP_HEIGHT;
	//m_hp = FIRE_KNIGHT_HP;

	m_speed = FIRE_KNIGHT_SPEED;
	//m_rollSpeed = FIRE_KNIGHT_ROLL_SPEED;
}

void FireKnight::updateAttackHitbox()
{
	m_attackHitboxWidth = 0.f;
	m_attackHitboxHeight = 0.f;

	m_attackHitboxPosition = sf::Vector2f{ -100.f, -100.f };

	if (m_currentTexture == m_entityName + "Attack1")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_ATTACK_1_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_1_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_ATTACK_1_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_ATTACK_1_HEIGHT;
			
			m_damage = FIRE_KNIGHT_ATTACK_1_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Attack2")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_1_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_1_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_1_HEIGHT;

			m_attackHitboxPosition = getShapePosition() - sf::Vector2f{m_attackHitboxWidth * static_cast<float>(m_facingRight), 0.f};
		}
		else if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_2_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_2_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_2_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_2_HEIGHT;
		}
		else if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_3_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_3_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_3_HEIGHT;

			m_attackHitboxPosition = getShapePosition() - sf::Vector2f{m_attackHitboxWidth * static_cast<float>(m_facingRight), 0.f};
		}
		else if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_4_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_4_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_4_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_4_HEIGHT;
		}

		m_damage = FIRE_KNIGHT_ATTACK_2_DAMAGE;
	}
	else if (m_currentTexture == m_entityName + "AirAttack")
	{
		m_attackHitboxPosition = getShapePosition() - sf::Vector2f{0.f, 15.f};

		if (m_frameCount >= FIRE_KNIGHT_AIR_ATTACK_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_AIR_ATTACK_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_AIR_ATTACK_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_AIR_ATTACK_HEIGHT;

			m_damage = FIRE_KNIGHT_AIR_ATTACK_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Ultimate")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_ULTIMATE_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ULTIMATE_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = FIRE_KNIGHT_ULTIMATE_WIDTH;
			m_attackHitboxHeight = FIRE_KNIGHT_ULTIMATE_HEIGHT;

			m_damage = FIRE_KNIGHT_ULTIMATE_DAMAGE;
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
