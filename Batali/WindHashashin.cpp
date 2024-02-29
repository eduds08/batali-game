#include "WindHashashin.h"

WindHashashin::WindHashashin(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: Character{ firstPosition, playerNumber, isBot, player }
{
	m_hitboxHeight = constants::windHashashinSwordHitboxHeight;

	// DEBUG
	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 0;
	m_attack1EndingFrame = 4;
	m_attack2StartingFrame = 1;
	m_attack2EndingFrame = 7;
	m_airAttackingStartingFrame = 2;
	m_airAttackingEndingFrame = 5;

	m_entityName = "wind_hashashin";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = constants::windHashashinSpriteWidth;
	m_spriteHeight = constants::windHashashinSpriteHeight;
	changeCurrentTexture(m_texturesActionName.at("Falling"), m_texturesNamePath.at(m_texturesActionName.at("Falling")), true);
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::windHashashinShapeWidth, constants::windHashashinShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = constants::windHashashinJumpHeight;
	m_hp = constants::windHashashinHp;

	if (m_isBot)
	{
		// Generates a random seed
		std::random_device rd;
		// Mersenne Twister random number generator
		std::mt19937 gen(rd());
		// Generates uniform distributed random number in a specific interval
		std::uniform_real_distribution<> distribution1(constants::minBotSpeed, constants::maxBotSpeed);
		std::uniform_real_distribution<> distribution2(constants::minBotDistanceFromPlayer, constants::maxBotDistanceFromPlayer);

		m_speed = static_cast<float>(distribution1(gen));
		m_distanceFromPlayer = static_cast<float>(distribution2(gen));
	}
	else
	{
		m_speed = constants::windHashashinSpeed;
	}

	m_hitboxWidthAttack1 = constants::windHashashinSwordHitboxWidthAttack1;
	m_hitboxWidthAttack2 = constants::windHashashinSwordHitboxWidthAttack2;
	m_hitboxWidthAirAttack = constants::windHashashinSwordHitboxWidthAirAttacking;

	m_attack1Damage = constants::windHashashinAttack1Damage;
	m_attack2Damage = constants::windHashashinAttack2Damage;
	m_airAttackDamage = constants::windHashashinAirAttackDamage;
}

void WindHashashin::updateHitbox()
{
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) ||
		(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame) ||
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
