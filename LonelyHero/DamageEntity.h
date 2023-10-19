#pragma once

#include "MovableEntity.h"

class DamageEntity : public MovableEntity
{
public:
	DamageEntity(sf::Vector2f firstPosition);
	virtual ~DamageEntity() = default;

	void updateCooldownDamage();
	void takeDamage(float& deltaTime, float attackDirection, const sf::FloatRect& attackHitbox);

	void knockbackMove(float& deltaTime, float attackDirection);

	virtual bool getInDamageCooldown() { return m_inDamageCooldown; }
	bool isDead() { return m_dead; }

	virtual void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }

protected:
	sf::Clock m_cooldownDamageClock{};
	float m_cooldownDamage{};

	bool m_dead{ false };
	bool m_dying{ false };
	bool m_inDamageCooldown{ false };

	bool m_hitted{ false };

	float m_knockbackVelocity{ constants::knockbackSpeed };

	int m_hp{};
};
