#pragma once

#include "SwordEntity.h"
#include "Projectile.h"
#include <memory>

class ProjectileEntity : public SwordEntity
{
public:
	ProjectileEntity();
	virtual ~ProjectileEntity() = default;

	virtual void update(float& deltaTime);
	
	// Instantiate a projectile and pushes it into m_projectiles vector
	void launchProjectile(const sf::Vector2f& offsetPosition, const std::string& projectileEntityName);
	
	// Update projectiles and checks if those needs to be deleted
	void updateProjectileEntity(float& deltaTime);

	/* GETTERS */

	const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }
	
protected:
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};
};
