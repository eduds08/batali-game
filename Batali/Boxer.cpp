#include "Boxer.h"

Boxer::Boxer(sf::Vector2f firstPosition, int playerNumber, bool isBot, std::shared_ptr<Character> player)
	: Character{ playerNumber, isBot, player }
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

	if (m_isBot)
	{
		m_speed = ENEMY_SPEED;
		m_distanceFromPlayer = ENEMY_DISTANCE_FROM_PLAYER;
	}
	else
	{
		m_speed = BOXER_SPEED;
	}
}

Boxer::~Boxer()
{
	if (m_ultimateProjectile != nullptr)
	{
		delete m_ultimateProjectile;
		m_ultimateProjectile = nullptr;
	}
}

void Boxer::updateHitbox()
{
	m_hitboxWidth = 0.f;
	m_hitboxHeight = 0.f;

	m_hitboxPosition = sf::Vector2f{ -100.f, -100.f };

	if (m_currentTexture == m_entityName + "Attack1")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= BOXER_ATTACK_1_STARTING_FRAME && m_frameCount <= BOXER_ATTACK_1_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = BOXER_ATTACK_1_WIDTH;
			m_hitboxHeight = BOXER_ATTACK_1_HEIGHT;

			m_damage = BOXER_ATTACK_1_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Attack2")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= BOXER_ATTACK_2_STARTING_FRAME && m_frameCount <= BOXER_ATTACK_2_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = BOXER_ATTACK_2_WIDTH;
			m_hitboxHeight = BOXER_ATTACK_2_HEIGHT;

			m_damage = BOXER_ATTACK_2_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "AirAttack")
	{
		m_hitboxPosition = getShapePosition() - sf::Vector2f{0.f, 15.f};

		if (m_frameCount >= BOXER_AIR_ATTACK_STARTING_FRAME && m_frameCount <= BOXER_AIR_ATTACK_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = BOXER_AIR_ATTACK_WIDTH;
			m_hitboxHeight = BOXER_AIR_ATTACK_HEIGHT;

			m_damage = BOXER_AIR_ATTACK_DAMAGE;
		}
	}
	else if (m_currentTexture == m_entityName + "Ultimate")
	{
		m_hitboxPosition = getShapePosition();

		if (m_frameCount >= BOXER_ULTIMATE_STARTING_FRAME && m_frameCount <= BOXER_ULTIMATE_ENDING_FRAME && !m_animationEnd)
		{
			m_hitboxWidth = BOXER_ULTIMATE_WIDTH;
			m_hitboxHeight = BOXER_ULTIMATE_HEIGHT;

			m_damage = BOXER_ULTIMATE_DAMAGE;
		}

		if (m_ultimateProjectile == nullptr)
			launchUltimate();
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

void Boxer::launchUltimate()
{
	if (m_ultimateProjectile == nullptr)
	{
		m_ultimateProjectile = new Projectile(getShapePosition());
	}
}
