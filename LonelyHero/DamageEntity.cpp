#include "DamageEntity.h"

DamageEntity::DamageEntity(sf::Vector2f firstPosition)
	: MovableEntity{ firstPosition }
{
}

void DamageEntity::updateCooldownDamage()
{
	m_knockbackVelocity = constants::knockbackSpeed;

	if (m_hitted)
	{
		m_cooldownDamage = m_cooldownDamageClock.getElapsedTime().asSeconds();
		if (m_cooldownDamage > constants::cooldownDamageTime)
		{
			m_hitted = false;
		}
	}
}

void DamageEntity::takeDamage(float& deltaTime, float direction)
{
	if (!m_hitted && !m_dying)
	{
		m_hitted = true;
		m_hp -= 100;

		knockbackMove(deltaTime, direction);

		if (m_hp <= 0)
		{
			m_dying = true;
		}

		m_cooldownDamageClock.restart();
		m_cooldownDamage = 0.f;
	}
}

void DamageEntity::knockbackMove(float& deltaTime, float direction)
{
	if (direction < 0.f)
	{
		m_shape.move(sf::Vector2f{m_knockbackVelocity, 0.f} *deltaTime);
	}
	else
	{
		m_shape.move(sf::Vector2f{m_knockbackVelocity * -1.f, 0.f} *deltaTime);
	}

	m_sprite.setPosition(sf::Vector2f{ getPosition().x, getPosition().y - (m_spriteHeight - getSize().y) / 2.f});
}

void DamageEntity::handleKnockbackVelocity()
{
	if (m_isCollidingHorizontally)
	{
		m_knockbackVelocity = 0.f;
	}
}
