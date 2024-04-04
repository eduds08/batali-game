#pragma once

#include "ILaunchProjectilesComponent.h"

#include "Projectile.h"

class PlayerLaunchProjectilesComponent : public ILaunchProjectilesComponent
{
public:
	PlayerLaunchProjectilesComponent() = default;
	virtual ~PlayerLaunchProjectilesComponent();

	virtual void update(GameObject& gameObject, World& world, sf::RenderWindow& window, float& deltaTime);

	virtual void launchProjectile(GameObject& gameObject, std::unique_ptr<IProjectileTypeState> projectileTypeState);

	const std::vector<std::unique_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }

private:
	std::vector<std::unique_ptr<Projectile>> m_projectiles{};
};
