#include "DamageEntity.h"

DamageEntity::DamageEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: MovableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, entityName, shapeWidth, shapeHeight, firstPosition }
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

void DamageEntity::takeDamage(float& deltaTime)
{
	if (!m_hitted && !m_dying)
	{
		m_hitted = true;
		m_hp -= 100;

		knockbackMove(deltaTime);

		if (m_hp <= 0)
		{
			m_dying = true;
		}

		m_cooldownDamageClock.restart();
		m_cooldownDamage = 0.f;
	}
}

void DamageEntity::knockbackMove(float& deltaTime)
{
	m_shape.move(sf::Vector2f{m_knockbackVelocity * -1.f * m_facingRight, 0.f} * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f - (m_spriteHeight - m_shape.getSize().y)});
}

void DamageEntity::handleKnockbackVelocity()
{
	if (m_collisionDirection.x != 0.f)
	{
		m_knockbackVelocity = 0.f;
	}
}
