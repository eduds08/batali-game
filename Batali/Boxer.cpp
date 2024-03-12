#include "Boxer.h"

Boxer::Boxer(sf::Vector2f firstPosition)
	: ProjectileEntity{}
{
	m_entityName = "boxer";

	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = BOXER_SPRITE_WIDTH;
	m_spriteHeight = BOXER_SPRITE_HEIGHT;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ BOXER_SHAPE_WIDTH, BOXER_SHAPE_HEIGHT});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_attackHitbox.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = BOXER_JUMP_HEIGHT;
	m_hp = BOXER_HP;

	m_speed = BOXER_SPEED;

	/*if (m_isBot)
	{
		m_speed = ENEMY_SPEED;
		m_distanceFromPlayer = ENEMY_DISTANCE_FROM_PLAYER;
	}
	else
	{
		m_speed = BOXER_SPEED;
	}*/
}

void Boxer::updateAttackHitbox()
{
	m_attackHitboxWidth = 0.f;
	m_attackHitboxHeight = 0.f;

	m_attackHitboxPosition = sf::Vector2f{ -100.f, -100.f };

	if (m_currentTexture == m_entityName + "Attack1")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= BOXER_ATTACK_1_STARTING_FRAME && m_frameCount <= BOXER_ATTACK_1_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = BOXER_ATTACK_1_WIDTH;
			m_attackHitboxHeight = BOXER_ATTACK_1_HEIGHT;

			m_damage = BOXER_ATTACK_1_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Attack2")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount >= BOXER_ATTACK_2_STARTING_FRAME && m_frameCount <= BOXER_ATTACK_2_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = BOXER_ATTACK_2_WIDTH;
			m_attackHitboxHeight = BOXER_ATTACK_2_HEIGHT;

			m_damage = BOXER_ATTACK_2_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "AirAttack")
	{
		m_attackHitboxPosition = getShapePosition() - sf::Vector2f{0.f, 15.f};

		if (m_frameCount >= BOXER_AIR_ATTACK_STARTING_FRAME && m_frameCount <= BOXER_AIR_ATTACK_ENDING_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = BOXER_AIR_ATTACK_WIDTH;
			m_attackHitboxHeight = BOXER_AIR_ATTACK_HEIGHT;

			m_damage = BOXER_AIR_ATTACK_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Ultimate")
	{
		m_attackHitboxPosition = getShapePosition();

		if (m_frameCount == BOXER_ULTIMATE_PT_1_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = BOXER_ULTIMATE_WIDTH;
			m_attackHitboxHeight = BOXER_ULTIMATE_HEIGHT;

			m_damage = BOXER_ULTIMATE_DAMAGE;

			if (m_ultimateProjectiles.size() == 0)
				launchUltimate();
		}
		else if (m_frameCount == BOXER_ULTIMATE_PT_2_FRAME && !m_animationEnd)
		{
			m_attackHitboxWidth = BOXER_ULTIMATE_WIDTH;
			m_attackHitboxHeight = BOXER_ULTIMATE_HEIGHT;

			m_damage = BOXER_ULTIMATE_DAMAGE;

			if (m_ultimateProjectiles.size() == 1)
				launchUltimate();
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

void Boxer::launchUltimate()
{
	m_ultimateProjectiles.emplace_back(std::make_shared<Projectile>(getShapePosition(), m_facingRight));
}
