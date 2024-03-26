#pragma once

#include "Character.h"
#include "Projectile.h"
#include <memory>

class ProjectileCharacter : public Character
{
public:
	ProjectileCharacter(int playerNumber = 1);
	virtual ~ProjectileCharacter() = default;

	virtual void update(float& deltaTime);

	// Instantiate a projectile and pushes it into m_projectiles vector
	virtual void launchProjectile() = 0;

	// Update projectiles and checks if those needs to be deleted
	void updateProjectileCharacter(float& deltaTime);

	virtual void render(sf::RenderWindow& window, bool debugMode);

	virtual void updateAnimation();

	/* GETTERS */

	const std::vector<std::shared_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }
	
protected:
	std::vector<std::shared_ptr<Projectile>> m_projectiles{};
};
