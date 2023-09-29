#include "Enemy.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
	, m_playerPosition{ playerPosition }
{
}

void Enemy::update(float& deltaTime)
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

	if (!m_isAttacking)
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
