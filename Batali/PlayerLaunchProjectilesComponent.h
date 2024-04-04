#pragma once

#include "ILaunchProjectilesComponent.h"

#include "Projectile.h"

class PlayerLaunchProjectilesComponent : public ILaunchProjectilesComponent
{
public:
	PlayerLaunchProjectilesComponent() = default;
	virtual ~PlayerLaunchProjectilesComponent();

	virtual void update(GameObject& gameObject, World& world, sf::RenderWindow& window, float& deltaTime);

	virtual void launchProjectile(GameObject& gameObject, IProjectileTypeState* projectileTypeState);

	const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }

private:
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};
};
