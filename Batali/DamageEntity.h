#pragma once

#include "MovableEntity.h"

class DamageEntity : public MovableEntity
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

	const int& getHp() const { return m_hp; }

	const int& getRemainingManaToUltimate() const { return m_remainingManaToUltimate; }

	virtual void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }

	virtual void die() = 0;

	void setOnWindHashashinUltimate(bool onWindHashashinUltimate) { m_onWindHashashinUltimate = onWindHashashinUltimate; }
	bool getOnWindHashashinUltimate() { return m_onWindHashashinUltimate; }
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
