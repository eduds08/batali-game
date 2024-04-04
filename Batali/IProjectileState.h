#pragma once

class Projectile;

class IProjectileState
{
public:
	virtual ~IProjectileState() = default;

	virtual void update(Projectile& projectile) = 0;

	virtual void enter(Projectile& projectile) = 0;
};
