#pragma once

#include "ProjectileEntity.h"
#include "BoxerUltimateProjectile.h"

class Boxer : public ProjectileEntity
{
public:
	Boxer(sf::Vector2f firstPosition);
	virtual ~Boxer() = default;

	//void updateAttackHitbox();

	virtual void updateAttackHitbox();

	// Instantiate a projectile and pushes it into m_projectiles vector
	void launchProjectile();

protected:
	
};
