#include "Enemy.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
	, m_playerPosition{ playerPosition }
{
}

void Enemy::update(float& deltaTime)
{
	if (m_currentTexture == "enemyDead" && m_frameCount >= 9)
	{
		dead = true;
		m_hitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_hitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	if (m_currentTexture == "enemyHitted")
	{
		m_hitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_hitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	if (m_currentTexture != "enemyHitted" && !dead && m_currentTexture != "enemyDead")
	{

		updateMovement(deltaTime);

		timeBetweenAttacks = clock.getElapsedTime().asSeconds();
		if (m_velocity.x == 0.f && timeBetweenAttacks > 1.f)
		{
			m_isAttacking = true;
		}

		updateAttack("enemy");
		updateHitbox();

		move(18.f, deltaTime);
	}
	
}

void Enemy::updateMovement(float& deltaTime)
{
	m_velocity.x = 0.f;

	if (m_playerPosition.x < getPosition().x - 50.f)
	{
		m_isRunning = true;
		m_facingRight = -1;
		m_velocity.x -= constants::enemySpeed;
	}
	else if (m_playerPosition.x > getPosition().x + 50.f)
	{
		m_isRunning = true;
		m_facingRight = 1;
		m_velocity.x += constants::enemySpeed;
	}
	else
	{
		m_isRunning = false;
	}

	m_sprite.setScale(m_spriteScale * m_facingRight, m_spriteScale);

	m_velocity.y += constants::gravity * deltaTime;
}

void Enemy::updateTexture()
{
	if (hp <= 0)
	{
		changeCurrentTexture(10, "enemyDead", "./_DeathNoMovement2.png");
	}
	else if (justHitted)
	{
		changeCurrentTexture(1, "enemyHitted", "./_Hit2.png");
	}
	else if (!m_isAttacking)
	{
		m_isRunning ? changeCurrentTexture(constants::playerRunningAnimationFramesAmount, "enemyRunning", "./_Run2.png") : changeCurrentTexture(constants::playerIdleAnimationFramesAmount, "enemyIdle", "./_Idle2.png");
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == "enemyAttacking1" ? changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "enemyAttacking2", "./_Attack2NoMovement2.png") : changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "enemyAttacking1", "./_AttackNoMovement2.png");
		clock.restart();
		timeBetweenAttacks = 0.f;
	}
}
