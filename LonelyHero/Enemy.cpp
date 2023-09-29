#include "Enemy.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath, const sf::Vector2f& playerPosition, float spriteScale)
	: AttackEntity{ spriteWidth, spriteHeight, animationFramesAmount, shapeWidth, shapeHeight, firstPosition, spriteScale }
	, m_playerPosition{ playerPosition }
{
	setSpriteTexture(textureName, texturePath);
}

void Enemy::update(float& deltaTime)
{
	updateMovement(deltaTime);

	if (m_velocity.x == 0.f)
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
		if (m_isRunning)
		{
			changeCurrentTexture(constants::playerRunningAnimationFramesAmount, "enemyRunning", "./_Run2.png");
		}
		else
		{
			changeCurrentTexture(constants::playerIdleAnimationFramesAmount, "enemyIdle", "./_Idle2.png");
		}
	}
	else
	{
		timeBetweenAttacks = clock.getElapsedTime().asSeconds();
		if (timeBetweenAttacks > 1.f)
		{
			if (m_previousAttackingAnimation == "enemyAttacking1")
			{
				changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "enemyAttacking2", "./_Attack2NoMovement2.png");
			}
			else
			{
				changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "enemyAttacking1", "./_AttackNoMovement2.png");
			}
			clock.restart();
			timeBetweenAttacks = 0.f;
		}
		
	}
}
