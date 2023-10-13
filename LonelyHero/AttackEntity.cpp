#include "AttackEntity.h"

AttackEntity::AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: MovableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
	m_attackHitbox = { sf::RectangleShape{sf::Vector2f{0.f, 0.f}} };
	m_attackHitbox.setOrigin(sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight } / 2.f);

	m_attackHitbox.setOutlineColor(sf::Color::Red);
	m_attackHitbox.setOutlineThickness(1.f);
}

// Called if m_isAttacking is true
void AttackEntity::handleAttack(const std::string& entity)
{
	// Don't let the player move if it is attacking
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;

	// Stop the attack when attack animation ends (and also stores the current animation as the previous one so the next attack uses the other attacking animation)
	if ((m_currentTexture == entity + "Attacking2" && m_frameCount >= 5) || (m_currentTexture == entity + "Attacking1" && m_frameCount >= 3))
	{
		m_previousAttackingAnimation = m_currentTexture;
		m_isAttacking = false;
	}
}

void AttackEntity::updateHitbox(const std::string& entity)
{
	/*
	Quick note about the hitbox: it is just a shape rectangle. To spawn it, I only set a size and a position relative to the entity for it. In this state, it "exists".
	When is not attacking, I just set its size to 0 and the position to negative coords so it kinda "vanishes" and "doesn't exist".
	*/

	// "spawn" the hitbox only when the animation reaches a specific frame
	if ((m_currentTexture == entity + "Attacking1" && m_frameCount > 1) || (m_currentTexture == entity + "Attacking2" && m_frameCount > 2))
	{
		if (m_attackHitbox.getSize() == sf::Vector2f{0.f, 0.f})
		{
			m_attackHitbox.setSize(sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight });
			m_attackHitbox.setPosition(getPosition() + sf::Vector2f((20.f + getSize().x) * m_facingRight, 0.f));
		}
	}
	else
	{
		if (m_attackHitbox.getSize() == sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight })
		{
			m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
			m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		}
	}

	// If the hitbox "exists", update its position relative to the entity that is attacking
	if (m_attackHitbox.getSize() == sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight })
	{
		m_attackHitbox.setPosition(getPosition() + sf::Vector2f((20.f + getSize().x) * m_facingRight, 0.f));
	}
}

void AttackEntity::updateTakeDamage(const std::string& entity)
{
	knockbackVelocity = constants::knockbackSpeed;

	if (m_currentTexture == entity + "Hitted" && m_frameCount >= 2)
	{
		hitAltTemp = false;
	}

	m_cooldownDamage = m_cooldownDamageClock.getElapsedTime().asSeconds();
	if (m_cooldownDamage > 0.4f)
	{
		justHitted = false;
	}

	if (justHitted)
	{
		m_isRunning = false;
	}
}

void AttackEntity::takeDamage(float& deltaTime)
{
	if (!justHitted && !dead)
	{
		hitAltTemp = true;
		justHitted = true;
		hp -= 100;

		knockbackMove(deltaTime);

		m_cooldownDamageClock.restart();
		m_cooldownDamage = 0.f;
	}
}
