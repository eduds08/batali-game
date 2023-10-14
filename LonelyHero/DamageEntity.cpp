#include "DamageEntity.h"

DamageEntity::DamageEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: MovableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, entityName, shapeWidth, shapeHeight, firstPosition }
{
}

void DamageEntity::updateTakeDamage()
{
	m_knockbackVelocity = constants::knockbackSpeed;

	if (m_hitted)
	{
		m_cooldownDamage = m_cooldownDamageClock.getElapsedTime().asSeconds();
		if (m_cooldownDamage > 0.4f)
		{
			m_hitted = false;
		}
		else {
			m_isRunning = false;
		}
	}
}

void DamageEntity::takeDamage(float& deltaTime)
{
	if (!m_hitted && !m_dead)
	{
		m_hitted = true;
		m_hp -= 100;

		knockbackMove(deltaTime);

		m_cooldownDamageClock.restart();
		m_cooldownDamage = 0.f;

		if (m_hp <= 0)
		{
			m_dying = true;
		}
	}
}