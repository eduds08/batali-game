#pragma once

#include "ProjectileCharacter.h"
#include "BoxerUltimateProjectile.h"

class Boxer : public ProjectileCharacter
{
public:
	Boxer(sf::Vector2f firstPosition, int playerNumber = 1);
	virtual ~Boxer() = default;

	//void updateAttackHitbox();

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox);

	// Instantiate a projectile and pushes it into m_projectiles vector
	void launchProjectile();

protected:
	
};
