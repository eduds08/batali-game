#include "Enemy.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
	, m_playerPosition{ playerPosition }
{
	m_texturesActionName.emplace("Death", "enemyDeath");
	m_texturesActionName.emplace("Hitted", "enemyHitted");
	m_texturesActionName.emplace("Running", "enemyRunning");
	m_texturesActionName.emplace("Idle", "enemyIdle");
	m_texturesActionName.emplace("Attacking1", "enemyAttacking1");
	m_texturesActionName.emplace("Attacking2", "enemyAttacking2");

	m_texturesNamePath.emplace(m_texturesActionName.at("Death"), "./assets/enemy/_DeathNoMovement2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Hitted"), "./assets/enemy/_HitSpriteSheet2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Running"), "./assets/enemy/_Run2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Idle"), "./assets/enemy/_Idle2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking1"), "./assets/enemy/_AttackNoMovement2.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking2"), "./assets/enemy/_Attack2NoMovement2.png");
}

void Enemy::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_currentTexture == "enemyDeath" && m_frameCount >= 9)
	{
		dead = true;
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	// Only called if hp > 0
	if (!dead && m_currentTexture != "enemyDeath")
	{
		updateMovement(m_playerPosition.x < getPosition().x - 50.f, m_playerPosition.x > getPosition().x + 50.f, (m_playerPosition.y - constants::knightShapeHeight / 2.f) < (getPosition().y - getSize().y / 2.f), deltaTime);
		updateAttack();

		move(deltaTime);

		updateTakeDamage("enemy");
	}
}

void Enemy::updateAttack()
{
	m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();

	// Only attacks when the time after the previous attack is bigger than 1 second and the enemy is in a distance of 50px from the player
	if (m_velocity.x == 0.f && m_timeBetweenAttacks > 1.f && m_canJump)
	{
		m_isAttacking = true;
	}

	if (m_isAttacking)
	{
		handleAttack("enemy");
	}

	updateHitbox("enemy");
}

void Enemy::updateTexture()
{
	if (hp <= 0)
	{
		changeCurrentTexture(10, "enemyDeath", m_texturesNamePath.at("enemyDeath"));
	}
	else if (hitAltTemp)
	{
		changeCurrentTexture(constants::knightHitAnimationFramesAmount, "enemyHitted", m_texturesNamePath.at("enemyHitted"));
	}
	else if (!m_isAttacking)
	{
		m_isRunning ? changeCurrentTexture(constants::knightRunningAnimationFramesAmount, "enemyRunning", m_texturesNamePath.at("enemyRunning")) : changeCurrentTexture(constants::knightIdleAnimationFramesAmount, "enemyIdle", m_texturesNamePath.at("enemyIdle"));
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == "enemyAttacking1" ? changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "enemyAttacking2", m_texturesNamePath.at("enemyAttacking2")) : changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "enemyAttacking1", m_texturesNamePath.at("enemyAttacking1"));
		m_timeBetweenAttacksClock.restart();
		m_timeBetweenAttacks = 0.f;
	}
}
