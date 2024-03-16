#pragma once

#include "WalkingEntity.h"
#include "Ground.h"
#include <functional>



class WindHashashin;
class SwordEntity;

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

	// Sets m_dead to true and "zeroes" some attributes
	void die();

	bool isCollidingWithAttack(SwordEntity& attackingEntity, bool& isUltimateActivate);

	/* Setters */

	void setOnFreeze(bool onFreeze) { m_onFreeze = onFreeze; }
	void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }

	/* Getters */

	const bool getOnFreeze() const { return m_onFreeze; }
	const bool getHitted() const { return m_hitted; }
	const bool getDead() const { return m_dead; }
	const bool getDying() const { return m_dying; }
	const int* getHp() const { return &m_hp; }
	const int* getRemainingManaToUltimate() const { return &m_remainingManaToUltimate; }

	/* Pure Virtual Methods */

	virtual void resetAttackHitbox() = 0;

protected:
	// When m_inDamageCooldown is true, the entity is immune to attacks
	bool m_inDamageCooldown{ false };
	sf::Clock m_damageCooldownClock{};
	float m_damageCooldown{};

	// This attribute is useful to identify if entity can do action (move, attack, etc...) or not. For example, Wind Hashashin's ultimate makes the entity freeze.
	bool m_onFreeze{ false };

	// When this attribute is True, the entity damage cooldown timer is smaller, so it can be hit many times quickly (like on hashashin's ultimate that hits three times real quick)
	bool m_onFastHit{ false };

	bool m_dead{ false };
	bool m_dying{ false };

	// When m_hitted is true, the hitted sprite is set
	bool m_hitted{ false };

	float m_knockbackVelocity{ KNOCKBACK_SPEED };

	int m_hp{};

	int m_remainingManaToUltimate{ 5 };
};
