#include "ProjectileCharacter.h"

#include "DeadState.h"

ProjectileCharacter::ProjectileCharacter(int playerNumber)
	: Character{ playerNumber }
{
}

void ProjectileCharacter::update(float& deltaTime)
{
	if (dynamic_cast<DeadState*>(m_state) == nullptr)
	{
		updateProjectileCharacter(deltaTime);
	}

	Character::update(deltaTime);
}

void ProjectileCharacter::updateProjectileCharacter(float& deltaTime)
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

void ProjectileCharacter::render(sf::RenderWindow& window, bool debugMode)
{
	Character::render(window, debugMode);

	if (m_projectiles.size() > 0)
	{
		for (auto& projectile : m_projectiles)
		{
			window.draw(projectile->getSprite());

			if (debugMode)
			{
				window.draw(projectile->getShape());
			}
		}
	}
}

void ProjectileCharacter::updateAnimation()
{
	AnimatedEntity::updateAnimation();

	if (m_projectiles.size() > 0)
	{
		for (auto& projectile : m_projectiles)
		{
			projectile->updateAnimation();
		}
	}
}
