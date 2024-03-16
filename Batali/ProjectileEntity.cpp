#include "ProjectileEntity.h"

ProjectileEntity::ProjectileEntity()
	: SwordEntity{}
{
}

void ProjectileEntity::launchProjectile()
{
	m_projectiles.emplace_back(std::make_shared<Projectile>(getShapePosition() + sf::Vector2f{0.f, -7.f}, static_cast<float>(m_facingRight)));
}

void ProjectileEntity::updateProjectileEntity(float& deltaTime)
{
	std::vector<std::vector<std::shared_ptr<Projectile>>::iterator> collidedProjectiles{};

	for (std::vector<std::shared_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it)
	{
		(*it)->update(deltaTime);

		if ((*it)->m_collided && (*it)->m_vanished)
		{
			collidedProjectiles.emplace_back(it);
		}
	}

	for (int i = 0; i < collidedProjectiles.size(); ++i)
	{
		m_projectiles.erase(collidedProjectiles[i]);
	}

	updateSwordEntity(deltaTime);
}
