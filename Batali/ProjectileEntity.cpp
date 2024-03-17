#include "ProjectileEntity.h"

ProjectileEntity::ProjectileEntity()
	: SwordEntity{}
{
}

void ProjectileEntity::update(float& deltaTime)
{
	if (!m_dying)
	{
		updateProjectileEntity(deltaTime);
	}

	SwordEntity::update(deltaTime);
}

void ProjectileEntity::updateProjectileEntity(float& deltaTime)
{
	std::vector<std::vector<std::shared_ptr<Projectile>>::iterator> collidedProjectiles{};

	for (std::vector<std::shared_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it)
	{
		(*it)->update(deltaTime);

		if ((*it)->getVanished())
		{
			collidedProjectiles.emplace_back(it);
		}
	}

	for (int i = 0; i < collidedProjectiles.size(); ++i)
	{
		m_projectiles.erase(collidedProjectiles[i]);
	}
}
