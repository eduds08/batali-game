#pragma once

#include "SwordEntity.h"
#include "Projectile.h"
#include <memory>

class ProjectileEntity : public SwordEntity
{
public:
	ProjectileEntity();
	virtual ~ProjectileEntity() = default;
	
	void launchProjectile();
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};

	void updateProjectileEntity(float& deltaTime);
	
protected:

};
