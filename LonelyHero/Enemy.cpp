#include "Enemy.h"

Enemy::Enemy(sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: SwordEntity{ firstPosition }
	, m_playerPosition{ playerPosition }
{
	m_spriteWidth = constants::martialSpriteWidth;
	m_spriteHeight = constants::martialSpriteHeight;
	m_spriteScale = constants::martialSpriteScale;

	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture("enemyIdle", "./assets/enemy/_Idle.png"));

	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	m_entityName = "enemy";

	initTexturesMap();

	m_shape.setSize(sf::Vector2f{ constants::martialShapeWidth, constants::martialShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	m_shape.setPosition(firstPosition.x, firstPosition.y);

	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	m_speed = constants::enemySpeed;
}

void Enemy::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_dying && m_frameCount >= m_currentAnimationFramesAmount - 1)
	{
		die();
	}

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

	if (m_dying && !m_dead)
	{
		m_velocity.x = 0.f;
		m_velocity.y += constants::gravity * deltaTime;
		move(deltaTime);
	}
}
