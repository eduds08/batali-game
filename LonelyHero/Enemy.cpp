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
		m_dead = true;
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	// Only called if hp > 0
	if (!m_dying)
	{
		updateMovement(m_playerPosition.x < getPosition().x - 50.f, m_playerPosition.x > getPosition().x + 50.f, (m_playerPosition.y - constants::knightShapeHeight / 2.f) < (getPosition().y - getSize().y / 2.f), deltaTime);

		m_timeBetweenAttacks = m_timeBetweenAttacksClock.getElapsedTime().asSeconds();
		updateAttack((m_velocity.x == 0.f && m_timeBetweenAttacks > 0.2f));

		if (m_isAttacking)
		{
			m_timeBetweenAttacksClock.restart();
			m_timeBetweenAttacks = 0.f;
		}

		move(deltaTime);

		updateTakeDamage();
	}
}