#include "WindHashashin.h"

WindHashashin::WindHashashin(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: Character{ playerNumber, isBot, player }
{
	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);
	m_ultimateActivateHitbox.setFillColor(sf::Color{0, 0, 255, 50});
	m_ultimateActivateHitbox.setOutlineThickness(1.f);

	m_entityName = "wind_hashashin";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = WIND_HASHASHIN_SPRITE_WIDTH;
	m_spriteHeight = WIND_HASHASHIN_SPRITE_HEIGHT;
	changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ WIND_HASHASHIN_SHAPE_WIDTH, WIND_HASHASHIN_SHAPE_HEIGHT});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = WIND_HASHASHIN_JUMP_HEIGHT;
	m_hp = WIND_HASHASHIN_HP;

	if (m_isBot)
	{
		// Generates a random seed
		std::random_device rd;
		// Mersenne Twister random number generator
		std::mt19937 gen(rd());
		// Generates uniform distributed random number in a specific interval
		std::uniform_real_distribution<> distribution1(MIN_ENEMY_SPEED, MAX_ENEMY_SPEED);
		std::uniform_real_distribution<> distribution2(MIN_ENEMY_DISTANCE_FROM_PLAYER, MAX_ENEMY_DISTANCE_FROM_PLAYER);

		m_speed = static_cast<float>(distribution1(gen));
		m_distanceFromPlayer = static_cast<float>(distribution2(gen));
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
		if (m_frameCount >= WIND_HASHASHIN_ACTIVATE_ULTIMATE_STARTING_FRAME && m_frameCount <= WIND_HASHASHIN_ACTIVATE_ULTIMATE_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = 0.f;
			m_hitboxHeight = 0.f;

			m_hitboxPosition = sf::Vector2f{ -100.f, -100.f };

			m_ultimateActivateHitbox.setSize(sf::Vector2f{WIND_HASHASHIN_ACTIVATE_ULTIMATE_WIDTH, WIND_HASHASHIN_ACTIVATE_ULTIMATE_HEIGHT});
			m_ultimateActivateHitbox.setOrigin(0.f, WIND_HASHASHIN_ACTIVATE_ULTIMATE_HEIGHT / 2.f);
			m_ultimateActivateHitbox.setScale(static_cast<float>(m_facingRight), 1.f);
			m_ultimateActivateHitbox.setPosition(getShapePosition());
		}
		else if ((m_frameCount == WIND_HASHASHIN_ULTIMATE_FIRST_FRAME || m_frameCount == WIND_HASHASHIN_ULTIMATE_SECOND_FRAME || m_frameCount == WIND_HASHASHIN_ULTIMATE_THIRD_FRAME) && !m_animationEnd)
		{
			m_hitboxWidth = getShapeSize().x;
			m_hitboxHeight = getShapeSize().y;

			m_hitboxPosition = getShapePosition();

			m_ultimateActivateHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
			m_ultimateActivateHitbox.setPosition(-100.f, -100.f);
		}

		m_damage = WIND_HASHASHIN_ULTIMATE_DAMAGE;
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
