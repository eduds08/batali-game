#include "FireKnight.h"

FireKnight::FireKnight(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: Character{ playerNumber, isBot, player }
{
	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	m_entityName = "fire_knight";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = FIRE_KNIGHT_SPRITE_WIDTH;
	m_spriteHeight = FIRE_KNIGHT_SPRITE_HEIGHT;
	changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ FIRE_KNIGHT_SHAPE_WIDTH, FIRE_KNIGHT_SHAPE_HEIGHT});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = FIRE_KNIGHT_JUMP_HEIGHT;
	m_hp = FIRE_KNIGHT_HP;

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
		m_speed = FIRE_KNIGHT_SPEED;
	}
}

void FireKnight::updateHitbox()
{
	m_hitboxWidth = 0.f;
	m_hitboxHeight = 0.f;

	m_hitboxPosition = sf::Vector2f{ -100.f, -100.f };

	if (m_currentTexture == m_entityName + "Attack1")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_ATTACK_1_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_1_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_ATTACK_1_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_ATTACK_1_HEIGHT;
			
			m_damage = FIRE_KNIGHT_ATTACK_1_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Attack2")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_1_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_1_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_1_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_1_HEIGHT;

			m_hitboxPosition = getShapePosition() - sf::Vector2f{m_hitboxWidth * m_facingRight, 0.f};
		}
		else if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_2_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_2_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_2_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_2_HEIGHT;
		}
		else if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_3_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_3_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_3_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_3_HEIGHT;

			m_hitboxPosition = getShapePosition() - sf::Vector2f{m_hitboxWidth * m_facingRight, 0.f};
		}
		else if (m_frameCount >= FIRE_KNIGHT_ATTACK_2_PT_4_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ATTACK_2_PT_4_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_ATTACK_2_PT_4_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_ATTACK_2_PT_4_HEIGHT;
		}

		m_damage = FIRE_KNIGHT_ATTACK_2_DAMAGE;
	}
	else if (m_currentTexture == m_entityName + "AirAttack")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_AIR_ATTACK_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_AIR_ATTACK_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_AIR_ATTACK_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_AIR_ATTACK_HEIGHT;

			m_damage = FIRE_KNIGHT_AIR_ATTACK_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Ultimate")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= FIRE_KNIGHT_ULTIMATE_STARTING_FRAME && m_frameCount <= FIRE_KNIGHT_ULTIMATE_ENDING_FRAME)
		{
			m_hitboxWidth = FIRE_KNIGHT_ULTIMATE_WIDTH;
			m_hitboxHeight = FIRE_KNIGHT_ULTIMATE_HEIGHT;

			m_damage = FIRE_KNIGHT_ULTIMATE_DAMAGE;
		}
	}
	else
	{
		m_damage = 0;
	}

	m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
	m_attackHitbox.setOrigin(sf::Vector2f{0.f, m_hitboxHeight / 2.f});
	m_attackHitbox.setScale(m_facingRight, 1.f);
	m_attackHitbox.setPosition(m_hitboxPosition);
}
