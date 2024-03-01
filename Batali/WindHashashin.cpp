#include "WindHashashin.h"

WindHashashin::WindHashashin(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: Character{ firstPosition, playerNumber, isBot, player }
{
	m_hitboxHeight = WIND_HASHASHIN_ATTACK_HEIGHT;

	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 0;
	m_attack1EndingFrame = 4;
	m_attack2StartingFrame = 1;
	m_attack2EndingFrame = 7;
	m_airAttackingStartingFrame = 12;
	m_airAttackingEndingFrame = 14;

	m_ultimateStartingFrame = 4;
	m_ultimateEndingFrame = 7;

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

	m_hitboxWidthAttack1 = WIND_HASHASHIN_ATTACK_1_WIDTH;
	m_hitboxWidthAttack2 = WIND_HASHASHIN_ATTACK_2_WIDTH;
	m_hitboxWidthAirAttack = WIND_HASHASHIN_AIR_ATTACK_WIDTH;
	m_hitboxWidthUltimate = WIND_HASHASHIN_ULTIMATE_WIDTH;

	m_attack1Damage = WIND_HASHASHIN_ATTACK_1_DAMAGE;
	m_attack2Damage = WIND_HASHASHIN_ATTACK_2_DAMAGE;
	m_airAttackDamage = WIND_HASHASHIN_AIR_ATTACK_DAMAGE;
	m_ultimateDamage = WIND_HASHASHIN_ULTIMATE_DAMAGE;
}

void WindHashashin::updateHitbox()
{
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) ||
		(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame) ||
		(m_currentTexture == m_entityName + "Ultimate" && m_frameCount > m_ultimateStartingFrame && m_frameCount < m_ultimateEndingFrame) ||
		(m_currentTexture == m_entityName + "AirAttacking" && m_frameCount > m_airAttackingStartingFrame && m_frameCount < m_airAttackingEndingFrame))
	{
		m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
		m_attackHitbox.setPosition(getShapePosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
	}
	else
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
}
