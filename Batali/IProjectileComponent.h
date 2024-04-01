#pragma once

class Player;
class World;

#include "Projectile.h"

class IProjectileComponent
{
public:
	virtual ~IProjectileComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime) = 0;

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile() = 0;

	virtual const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const = 0;
};
