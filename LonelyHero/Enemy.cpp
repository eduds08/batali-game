#include "Enemy.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
	, m_playerPosition{ playerPosition }
{
}

void Enemy::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_currentTexture == "knightDead" && m_frameCount >= 9)
	{
		dead = true;
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	// Only called if hp > 0
	if (!dead && m_currentTexture != "knightDead")
	{
		updateMovement(deltaTime);
		updateAttack();

		move(m_spriteHeight - m_shape.getSize().y, deltaTime);
	}
}

void Enemy::updateMovement(float& deltaTime)
{
	m_velocity.x = 0.f;
	m_isRunning = true;

	if (m_playerPosition.x < getPosition().x - 50.f)
	{
		m_facingRight = -1;
		m_velocity.x -= constants::enemySpeed;
	}
	else if (m_playerPosition.x > getPosition().x + 50.f)
	{
		m_facingRight = 1;
		m_velocity.x += constants::enemySpeed;
	}
	else
	{
		m_isRunning = false;
	}

	flipSprite();

	m_velocity.y += constants::gravity * deltaTime;
}

void Enemy::updateAttack()
{
	timeBetweenAttacks = clock.getElapsedTime().asSeconds();

	// Only attacks when the time after the previous attack is bigger than 1 second and the enemy is in a distance of 50px from the player
	if (m_velocity.x == 0.f && timeBetweenAttacks > 1.f)
	{
		m_isAttacking = true;
	}

	if (m_isAttacking)
	{
		handleAttack("knight");
	}

	updateHitbox("knight");
}

void Enemy::updateTexture()
{
	if (hp <= 0)
	{
		changeCurrentTexture(10, "knightDead", "./_DeathNoMovement2.png");
	}
	else if (!m_isAttacking)
	{
		m_isRunning ? changeCurrentTexture(constants::knightRunningAnimationFramesAmount, "knightRunning", "./_Run2.png") : changeCurrentTexture(constants::knightIdleAnimationFramesAmount, "knightIdle", "./_Idle2.png");
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == "knightAttacking1" ? changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "knightAttacking2", "./_Attack2NoMovement2.png") : changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "knightAttacking1", "./_AttackNoMovement2.png");
		clock.restart();
		timeBetweenAttacks = 0.f;
	}
}
