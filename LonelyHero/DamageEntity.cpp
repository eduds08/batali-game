#include "DamageEntity.h"

DamageEntity::DamageEntity(sf::Vector2f firstPosition)
	: MovableEntity{ firstPosition }
{
}

void DamageEntity::updateDamage()
{
	// handleCollision() is called after this, so if the entity collides with a wall, knockback is set to 0
	m_knockbackVelocity = constants::knockbackSpeed;

	// Makes sure the Hitted animation is only played once per attack
	if (m_currentTexture == m_texturesActionName.at("Hitted") && m_frameCount >= m_currentAnimationFramesAmount)
	{
		m_hitted = false;


		if (m_hp <= 0)
		{
			m_dying = true;
		}
	}

	// While on damageCooldown, the entity is immune to attacks. Useful to make the entity being hit only once per attack
	m_damageCooldown = m_damageCooldownClock.getElapsedTime().asSeconds();
	if (m_damageCooldown > constants::cooldownDamageTime)
	{
		m_inDamageCooldown = false;
	}
}

void DamageEntity::takeDamage(float& deltaTime, float attackDirection, int damage)
{
	// Only executed if not already dead and when not immune (on damageCooldown)
	if (!m_inDamageCooldown && !m_dying && !m_onRoll)
	{
		m_inDamageCooldown = true;
		m_hitted = true;

		m_hp -= damage;

		if (attackDirection < 0.f)
		{
			// attack coming from left
			if (m_facingRight == 1)
			{
				m_facingRight = -1;
				flipSprite();
			}
		}
		else
		{
			// attack coming from right
			if (m_facingRight == -1)
			{
				m_facingRight = 1;
				flipSprite();
			}
		}
		
		m_damageCooldownClock.restart();
		m_damageCooldown = 0.f;
	}
}

void DamageEntity::knockbackMove(float& deltaTime, float attackDirection)
{
	if (attackDirection < 0.f)
	{
		// attack coming from left
		m_shape.move(sf::Vector2f{m_knockbackVelocity, 0.f} *deltaTime);
	}
	else
	{
		// attack coming from right
		m_shape.move(sf::Vector2f{m_knockbackVelocity * -1.f, 0.f} *deltaTime);
	}

	m_sprite.setPosition(sf::Vector2f{ getPosition().x, getPosition().y - (m_spriteHeight - getSize().y) / 2.f});
}

void DamageEntity::updateDeath()
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_currentTexture == m_texturesActionName.at("Death") && m_frameCount >= m_currentAnimationFramesAmount && !m_dead)
	{
		die();
	}
}

void DamageEntity::updateGravityWhenDying(float& deltaTime)
{
	if (m_dying)
	{
		m_velocity.x = 0.f;
		m_velocity.y += constants::gravity * deltaTime;
		move(deltaTime);
	}
}
