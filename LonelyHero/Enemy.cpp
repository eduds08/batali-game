#include "Enemy.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition)
	: SwordEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, entityName, shapeWidth, shapeHeight, firstPosition }
	, m_playerPosition{ playerPosition }
{
}

void Enemy::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_dying && m_frameCount >= 9)
	{
		die();
	}

	// Only called if hp > 0
	if (!m_dying)
	{
		bool conditionRunLeft = m_playerPosition.x < getPosition().x - 50.f;
		bool conditionRunRight = m_playerPosition.x > getPosition().x + 50.f;
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