#pragma once

#include "CharacterWithProjectiles.h"
#include "BoxerUltimateProjectile.h"

class Boxer : public CharacterWithProjectiles
{
public:
	Boxer(sf::Vector2f firstPosition);
	virtual ~Boxer() = default;

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox);

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile();
};
