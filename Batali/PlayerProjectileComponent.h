#pragma once

#include "IProjectileComponent.h"

#include "Projectile.h"

class PlayerProjectileComponent : public IProjectileComponent
{
public:
	PlayerProjectileComponent() = default;
	virtual ~PlayerProjectileComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime);

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile();

	// update projectile's animation in animatingComponent (pass this component as reference, maybe idk)

	const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }

private:
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};

};
