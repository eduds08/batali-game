#include "ProjectileCollisionComponent.h"

#include "GameObject.h"
#include "Player.h"

#include "Projectile.h"

#include "World.h"

void ProjectileCollisionComponent::update(GameObject& gameObject, World& world)
{
	Projectile* projectile = dynamic_cast<Projectile*>(&gameObject);

	// check collision with world entities and tiles
	for (auto& player : world.m_players)
	{
		// logic to diferentiate player who launched the projectile
		if (player->getId() != projectile->getLauncher().getId())
		{
			if (gameObject.getShape().getGlobalBounds().intersects(player->getShape().getGlobalBounds()))
			{
				projectile->setCollided(true);
				player->handleHitted(projectile->getDamage(), 0.f);
				// logic to hit the enemy here
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

	//if (projectile->getCollided() && animationEnd)
	// logic to vanish idk
}
