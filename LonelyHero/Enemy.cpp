#include "Enemy.h"

Enemy::Enemy(sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: SwordEntity{ firstPosition }
	, m_playerPosition{ playerPosition }
{
	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 4;
	m_attack1EndingFrame = 7;
	m_attack2StartingFrame = 3;
	m_attack2EndingFrame = 7;

	// Initialize sprite
	m_spriteWidth = constants::knightSpriteWidth;
	m_spriteHeight = constants::knightSpriteHeight;
	m_spriteScale = constants::knightSpriteScale;
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture("enemyIdle", "./assets/enemy/_Idle.png"));
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::knightShapeWidth, constants::knightShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_entityName = "enemy";
	initTexturesMap();
	m_speed = constants::enemySpeed;
	m_jumpHeight = constants::enemyJumpHeight;
	m_hp = constants::enemyHp;
}

void Enemy::update(float& deltaTime)
{
	// Checks if entity is dead
	updateDeath();

	// Only called if hp > 0
	if (!m_dying)
	{
		bool conditionRunLeft = m_playerPosition.x < getPosition().x - constants::enemyDistanceFromPlayer;
		bool conditionRunRight = m_playerPosition.x > getPosition().x + constants::enemyDistanceFromPlayer;
		bool conditionJump = (((m_playerPosition.y - constants::knightShapeHeight / 2.f) < (getPosition().y - getSize().y / 2.f)) && m_isCollidingHorizontally);

		updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime);

		m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
		bool conditionAttack = (m_velocity.x == 0.f && m_timeBetweenAttacks > constants::timeBetweenEnemyAttacks);

		updateAttack(conditionAttack);

		if (m_isAttacking)
		{
			m_timeBetweenAttacksClock.restart();
			m_timeBetweenAttacks = 0.f;
		}

		move(deltaTime);

		updateCooldownDamage();
	}

	// Add gravity when on dying state
	updateGravityWhenDying(deltaTime);

	updateLimits();
}
