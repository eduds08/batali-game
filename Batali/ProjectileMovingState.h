#pragma once

#include "IProjectileState.h"

class ProjectileMovingState : public IProjectileState
{
public:
	ProjectileMovingState() = default;
	virtual ~ProjectileMovingState() = default;

	virtual void update(Projectile& projectile);

	virtual void enter(Projectile& projectile);
};
