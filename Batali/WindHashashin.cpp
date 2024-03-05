#include "WindHashashin.h"

WindHashashin::WindHashashin(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: Character{ playerNumber, isBot, player }
{
	m_entityName = "wind_hashashin";

	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = WIND_HASHASHIN_SPRITE_WIDTH;
	m_spriteHeight = WIND_HASHASHIN_SPRITE_HEIGHT;
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ WIND_HASHASHIN_SHAPE_WIDTH, WIND_HASHASHIN_SHAPE_HEIGHT});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{ 255, 0, 0, 50 });
	m_attackHitbox.setOutlineThickness(1.f);
	m_ultimateActivateHitbox.setFillColor(sf::Color{ 0, 0, 255, 50 });
	m_ultimateActivateHitbox.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = WIND_HASHASHIN_JUMP_HEIGHT;
	m_hp = WIND_HASHASHIN_HP;

	if (m_isBot)
	{
		m_speed = ENEMY_SPEED;
		m_distanceFromPlayer = ENEMY_DISTANCE_FROM_PLAYER;
	}
	else
	{
		m_speed = WIND_HASHASHIN_SPEED;
	}
}

void WindHashashin::updateHitbox()
{
	m_hitboxWidth = 0.f;
	m_hitboxHeight = 0.f;

	m_hitboxPosition = sf::Vector2f{ -100.f, -100.f };

	m_ultimateActivateHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
	m_ultimateActivateHitbox.setPosition(-100.f, -100.f);

	if (m_currentTexture == m_entityName + "Attack1")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= WIND_HASHASHIN_ATTACK_1_PT_1_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ATTACK_1_PT_1_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = WIND_HASHASHIN_ATTACK_1_PT_1_WIDTH;
			m_hitboxHeight = WIND_HASHASHIN_ATTACK_1_PT_1_HEIGHT;
		}
		else if (m_frameCount >= WIND_HASHASHIN_ATTACK_1_PT_2_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ATTACK_1_PT_2_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = WIND_HASHASHIN_ATTACK_1_PT_2_WIDTH;
			m_hitboxHeight = WIND_HASHASHIN_ATTACK_1_PT_2_HEIGHT;
		}

		m_damage = WIND_HASHASHIN_ATTACK_1_DAMAGE;
	}
	else if (m_currentTexture == m_entityName + "Attack2")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= WIND_HASHASHIN_ATTACK_2_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ATTACK_2_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = WIND_HASHASHIN_ATTACK_2_WIDTH;
			m_hitboxHeight = WIND_HASHASHIN_ATTACK_2_HEIGHT;

			m_damage = WIND_HASHASHIN_ATTACK_2_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "AirAttack")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= WIND_HASHASHIN_AIR_ATTACK_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_AIR_ATTACK_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = WIND_HASHASHIN_AIR_ATTACK_WIDTH;
			m_hitboxHeight = WIND_HASHASHIN_AIR_ATTACK_HEIGHT;

			m_damage = WIND_HASHASHIN_AIR_ATTACK_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Ultimate")
	{
		m_damage = WIND_HASHASHIN_ULTIMATE_DAMAGE;

		if (m_frameCount >= WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = 0.f;
			m_hitboxHeight = 0.f;

			m_hitboxPosition = sf::Vector2f{ -100.f, -100.f };

			m_ultimateActivateHitbox.setSize(getShapeSize());
			m_ultimateActivateHitbox.setOrigin(getShapeSize() / 2.f);
			m_ultimateActivateHitbox.setScale(static_cast<float>(m_facingRight), 1.f);
			m_ultimateActivateHitbox.setPosition(getShapePosition() + sf::Vector2f{getShapeSize().x * 2 * (m_frameCount - 5) * m_facingRight, 0.f});
		}
		else if ((m_frameCount == WIND_HASHASHIN_ULTIMATE_FIRST_FRAME || m_frameCount == WIND_HASHASHIN_ULTIMATE_SECOND_FRAME || m_frameCount == WIND_HASHASHIN_ULTIMATE_THIRD_FRAME) && !m_animationEnd)
		{
			m_hitboxWidth = getShapeSize().x;
			m_hitboxHeight = getShapeSize().y;

			m_hitboxPosition = getShapePosition();

			m_ultimateActivateHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
			m_ultimateActivateHitbox.setPosition(-100.f, -100.f);

			m_damage = WIND_HASHASHIN_ULTIMATE_DAMAGE;
		}
		else if (m_frameCount > WIND_HASHASHIN_ULTIMATE_THIRD_FRAME && !m_animationEnd)
		{
			m_damage = 0;
		}
	}
	else
	{
		m_damage = 0;
	}

	m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
	m_attackHitbox.setOrigin(0.f, m_hitboxHeight / 2.f);
	m_attackHitbox.setScale(static_cast<float>(m_facingRight), 1.f);
	m_attackHitbox.setPosition(m_hitboxPosition);
}
