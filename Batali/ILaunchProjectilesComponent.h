#pragma once

class GameObject;
class World;

#include "Projectile.h"

class ILaunchProjectilesComponent
{
public:
	virtual ~ILaunchProjectilesComponent() = default;

	virtual void update(GameObject& gameObject, World& world, float& deltaTime) = 0;

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile(GameObject& gameObject) = 0;

	virtual const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const = 0;
};
