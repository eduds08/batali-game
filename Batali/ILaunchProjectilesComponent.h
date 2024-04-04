#pragma once

class GameObject;
class World;

#include "Projectile.h"

class ILaunchProjectilesComponent
{
public:
	virtual ~ILaunchProjectilesComponent() = default;

	virtual void update(GameObject& gameObject, World& world, sf::RenderWindow& window, float& deltaTime) = 0;

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile(GameObject& gameObject, IProjectileTypeState* projectileTypeState) = 0;

	virtual const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const = 0;
};
