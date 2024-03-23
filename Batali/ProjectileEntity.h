#pragma once

#include "Character.h"
#include "Projectile.h"
#include <memory>

class ProjectileEntity : public Character
{
public:
	ProjectileEntity();
	virtual ~ProjectileEntity() = default;

	virtual void update(float& deltaTime);
	
	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile() = 0;
	
	// Update projectiles and checks if those needs to be deleted
	void updateProjectileEntity(float& deltaTime);

	/* GETTERS */

	const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }
	
protected:
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};
};
