#include "PlayerLaunchProjectilesComponent.h"

#include "Player.h"
#include "World.h"

PlayerLaunchProjectilesComponent::~PlayerLaunchProjectilesComponent()
{
	m_projectiles.clear();
}

void PlayerLaunchProjectilesComponent::update(GameObject& gameObject, World& world, sf::RenderWindow& window, float& deltaTime)
{
	std::vector<std::vector<std::shared_ptr<Projectile>>::iterator> collidedProjectiles{};

	for (std::vector<std::shared_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it)
	{
		(*it)->update(window, world, deltaTime);

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

void PlayerLaunchProjectilesComponent::launchProjectile(GameObject& gameObject, IProjectileTypeState* projectileTypeState)
{
	m_projectiles.emplace_back(std::make_shared<Projectile>(gameObject.getShape().getPosition() + BOXER_PROJECTILE_OFFSET_POSITION, static_cast<float>(gameObject.getFacingRight()), projectileTypeState));
}
