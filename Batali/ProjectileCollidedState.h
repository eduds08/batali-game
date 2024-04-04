#pragma once

#include "IProjectileState.h"

class ProjectileCollidedState : public IProjectileState
{
public:
	ProjectileCollidedState() = default;
	virtual ~ProjectileCollidedState() = default;

	virtual void update(Projectile& projectile);

	virtual void enter(Projectile& projectile);
};
