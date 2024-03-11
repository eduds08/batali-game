#pragma once

#include "WalkingEntity.h"

class DamageEntity : public WalkingEntity
{
public:
	DamageEntity();
	virtual ~DamageEntity() = default;

	// Updates attributes related to being attacked (Checks hitted animation, damage cooldown and knockback)
	void updateDamage();

	// Updates entity's attributes when it gets attacked (and returns if attackedEntity got hit or not)
	bool takeDamage(float& deltaTime, float attackDirection, int damage);

	// Moves the entity after being hit. attackDirection -> direction of the attack (from left or right)
	void knockbackMove(float& deltaTime, float attackDirection);

	// Checks if the entity died. If yes, calls method die()
	void updateDeath();

	// If the entity is dying (not dead yet), it doesn't move anymore, so we call this method to move it in y-direction and avoids it floating in the air after death
	void updateGravityWhenDying(float& deltaTime);

	virtual const bool getHitted() const { return m_hitted; }
	const bool isDead() const { return m_dead; }
	const bool isDying() const { return m_dying; }

	const int* getHp() const { return &m_hp; }

	const int* getRemainingManaToUltimate() const { return &m_remainingManaToUltimate; }

	virtual void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }

	// Sets m_dead to true and "zeroes" some attributes
	void die();

	void setOnWindHashashinUltimate(bool onWindHashashinUltimate) { m_onWindHashashinUltimate = onWindHashashinUltimate; }
	virtual const bool getOnWindHashashinUltimate() const { return m_onWindHashashinUltimate; }

	virtual void resetAttackHitbox() = 0;
	virtual void resetUltimateHitbox() = 0;
protected:
	sf::Clock m_damageCooldownClock{};
	float m_damageCooldown{};

	bool m_onWindHashashinUltimate{ false };

	bool m_dead{ false };
	bool m_dying{ false };

	// When m_inDamageCooldown is true, the entity is immune to attacks
	bool m_inDamageCooldown{ false };

	// When m_hitted is true, the hitted sprite is set
	bool m_hitted{ false };

	float m_knockbackVelocity{ KNOCKBACK_SPEED };

	int m_hp{};

	int m_remainingManaToUltimate{ 5 };
};
