#include "PlayerProjectileComponent.h"

#include "Player.h"
#include "World.h"

void PlayerProjectileComponent::update(Player& player, World& world, float& deltaTime)
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

void PlayerProjectileComponent::launchProjectile()
{
	//m_projectiles.emplace_back(std::make_shared<BoxerUltimateProjectile>(getShapePosition() + BOXER_PROJECTILE_OFFSET_POSITION, m_facingRight));
}
