#include "PlayerLaunchProjectilesComponent.h"

#include "Player.h"
#include "World.h"

PlayerLaunchProjectilesComponent::~PlayerLaunchProjectilesComponent()
{
	m_projectiles.clear();
}

void PlayerLaunchProjectilesComponent::update(GameObject& gameObject, World& world, sf::RenderWindow& window, float& deltaTime)
{
	for (std::vector<std::unique_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end();)
	{
		(*it)->update(window, world, deltaTime);

		if ((*it)->getVanished())
		{
			it = m_projectiles.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void PlayerLaunchProjectilesComponent::launchProjectile(GameObject& gameObject, std::unique_ptr<IProjectileTypeState> projectileTypeState)
{
	m_projectiles.emplace_back(std::make_unique<Projectile>(gameObject.getShape().getPosition() + BOXER_PROJECTILE_OFFSET_POSITION, static_cast<float>(gameObject.getFacingRight()), std::move(projectileTypeState), gameObject));
}
