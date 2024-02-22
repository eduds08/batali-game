#include "FireKnight.h"

FireKnight::FireKnight(sf::Vector2f firstPosition, int playerNumber, bool isBot, Character* player)
	: Character{ firstPosition, playerNumber, isBot, player }
{
	m_hitboxHeight = constants::fireKnightSwordHitboxHeight;

	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 4;
	m_attack1EndingFrame = 7;
	m_attack2StartingFrame = 1;
	m_attack2EndingFrame = 7;
	m_airAttackingStartingFrame = 3;
	m_airAttackingEndingFrame = 5;

	m_entityName = "fire_knight";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = constants::fireKnightSpriteWidth;
	m_spriteHeight = constants::fireKnightSpriteHeight;
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle"))));
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::fireKnightShapeWidth, constants::fireKnightShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_jumpHeight = constants::fireKnightJumpHeight;
	m_hp = constants::fireKnightHp;

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
		//m_speed = constants::playerSpeed + 40.f;
		m_distanceFromPlayer = static_cast<float>(distribution2(gen));
	}
	else
	{
		m_speed = constants::fireKnightSpeed;
	}
}

FireKnight::~FireKnight()
{
	if (m_player != nullptr)
	{
		delete m_player;
		m_player = nullptr;
	}
}

void FireKnight::updateHitbox()
{
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) ||
		(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame) ||
		(m_currentTexture == m_entityName + "AirAttacking" && m_frameCount > m_airAttackingStartingFrame && m_frameCount < m_airAttackingEndingFrame))
	{
		m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
		if (m_currentTexture == m_entityName + "Attacking2")
		{
			m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * 10.f / 2.f, 0.f));
		}
		else
		{
			m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
		}
	}
	else
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
}
