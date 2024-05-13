#include "ProjectileCollisionComponent.h"

#include "Projectile.h"
#include "World.h"

void ProjectileCollisionComponent::update(GameObject& gameObject, World& world)
{
	Projectile* projectile = dynamic_cast<Projectile*>(&gameObject);

	for (auto& player : world.m_players)
	{
		if (player->getId() != projectile->getLauncherId())
		{
			if (gameObject.getShape().getGlobalBounds().intersects(player->getShape().getGlobalBounds()) && player->m_currentState != "RollingState")
			{
				projectile->setCollided(true);
				player->setDamageToTake(projectile->getDamage());
				player->handleCondition("HITTED");
				player->setKnockbackVelocity(0.f);
			}
		}
	}

	for (auto& tile : world.m_tiles)
	{
		// logic to diferentiate player who launched the projectile
		if (gameObject.getShape().getGlobalBounds().intersects(tile.getSprite().getGlobalBounds()))
		{
			projectile->setCollided(true);
			break;
		}
	}
}
