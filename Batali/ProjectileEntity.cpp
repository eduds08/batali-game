#include "ProjectileEntity.h"

#include "DeadState.h"

ProjectileEntity::ProjectileEntity()
	: Character{}
{
}

void ProjectileEntity::update(float& deltaTime)
{
	if (dynamic_cast<DeadState*>(m_state) == nullptr)
	{
		updateProjectileEntity(deltaTime);
	}

	Character::update(deltaTime);
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
