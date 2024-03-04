#include "DamageEntity.h"

DamageEntity::DamageEntity()
	: MovableEntity{}
{
}

void DamageEntity::updateDamage()
{
	// handleCollision() is called after this, so if the entity collides with a wall, knockback is set to 0
	m_knockbackVelocity = KNOCKBACK_SPEED;

	// Makes sure the Hitted animation is only played once per attack
	if (m_hitted && m_animationEnd)
	{
		m_hitted = false;

		if (m_hp <= 0)
		{
			m_dying = true;
		}
	}

	// While on damageCooldown, the entity is immune to attacks. Useful to make the entity being hit only once per attack
	m_damageCooldown = m_damageCooldownClock.getElapsedTime().asSeconds();
	if (m_damageCooldown > COOLDOWN_IMMUNE_TIME)
	{
		m_inDamageCooldown = false;
	}
}

bool DamageEntity::takeDamage(float& deltaTime, float attackDirection, int damage)
{
	// Only executed if not already dead and when not immune (on damageCooldown or onRoll)
	if (!m_inDamageCooldown && !m_dying && !m_onRoll && !getOnUltimate())
	{
		m_inDamageCooldown = true;
		m_hitted = true;

		m_hp -= damage;

		if (m_remainingManaToUltimate > 0)
		{
			--m_remainingManaToUltimate;
		}

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

		return true;
	}

	return false;
}

void DamageEntity::knockbackMove(float& deltaTime, float attackDirection)
{
	if (attackDirection < 0.f)
	{
		// attack coming from left
		m_shape.move(sf::Vector2f{ m_knockbackVelocity, 0.f } *deltaTime);
	}
	else
	{
		// attack coming from right
		m_shape.move(sf::Vector2f{ m_knockbackVelocity * -1.f, 0.f } *deltaTime);
	}

	m_sprite.setPosition(sf::Vector2f{ getShapePosition().x, getShapePosition().y - (m_spriteHeight - getShapeSize().y) / 2.f });
}

void DamageEntity::updateDeath()
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_currentTexture == m_texturesActionName.at("Death") && !m_dead && m_animationEnd)
	{
		die();
	}
}

void DamageEntity::updateGravityWhenDying(float& deltaTime)
{
	if (m_dying)
	{
		m_velocity.x = 0.f;
		m_velocity.y += GRAVITY * deltaTime;
		move(deltaTime);
	}
}
