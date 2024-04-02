#pragma once

#include "ILaunchProjectilesComponent.h"

#include "Projectile.h"

class PlayerLaunchProjectilesComponent : public ILaunchProjectilesComponent
{
public:
	PlayerLaunchProjectilesComponent() = default;
	virtual ~PlayerLaunchProjectilesComponent() = default;

	virtual void update(GameObject& gameObject, World& world, sf::RenderWindow& window, float& deltaTime);

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile(GameObject& gameObject);

	// update projectile's animation in animatingComponent (pass this component as reference, maybe idk)

	const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }

private:
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};

};
