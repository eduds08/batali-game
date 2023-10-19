#include "DamageEntity.h"

DamageEntity::DamageEntity(sf::Vector2f firstPosition)
	: MovableEntity{ firstPosition }
{
}

// Called inside derived entity's Update()
void DamageEntity::updateCooldownDamage()
{
	// The handleCollision method is called after this, so if the entity collides with a wall, knockback is set to 0
	m_knockbackVelocity = constants::knockbackSpeed;

	// Makes sure the Hitted animation is only played once per attack
	if (m_hitted && m_frameCount >= m_currentAnimationFramesAmount)
	{
		m_hitted = false;
	}

	// While on CooldownDamage, the entity is immune to attacks. Useful to make the entity being hit only once per attack
	m_cooldownDamage = m_cooldownDamageClock.getElapsedTime().asSeconds();
	if (m_cooldownDamage > constants::cooldownDamageTime)
	{
		m_inDamageCooldown = false;
	}

	// HAVE TO REMEMBER!
	if (m_inDamageCooldown)
	{
		m_isRunning = false;
	}
}

// Called when hitted.
void DamageEntity::takeDamage(float& deltaTime, float attackDirection)
{
	// Only executed if not already dead and when not immune (on cooldownDamage)
	if (!m_inDamageCooldown && !m_dying)
	{
		m_inDamageCooldown = true;
		m_hitted = true;

		m_hp -= 100;

		if (m_hp <= 0)
		{
			m_dying = true;
		}

		m_cooldownDamageClock.restart();
		m_cooldownDamage = 0.f;
	}
}

// Moves the entity after being hit. attackDirection -> direction of the attack (from left or right)
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

// Check if the entity died. If yes, calls method die()
void DamageEntity::updateDeath()
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_dying && m_frameCount >= m_currentAnimationFramesAmount && !m_dead)
	{
		die();
	}
}

// If the entity is dying (not dead yet), it doesn't move anymore, so we call this method to move it in y-direction and avoids it floating in the air after death
void DamageEntity::updateGravityWhenDying(float& deltaTime)
{
	if (m_dying && !m_dead)
	{
		m_velocity.x = 0.f;
		m_velocity.y += constants::gravity * deltaTime;
		move(deltaTime);
	}
}
