#pragma once

#include "PlayerAttackComponent.h"

#include "Projectile.h"

class BoxerAttackComponent : public PlayerAttackComponent
{
public:
	BoxerAttackComponent() = default;
	virtual ~BoxerAttackComponent() = default;

	virtual void update(World& world, float& deltaTime);

	virtual void render(sf::RenderWindow& window);

	virtual void launchProjectile(std::unique_ptr<IProjectileTypeState> projectileTypeState);

	const std::vector<std::unique_ptr<Projectile>>& getProjectiles() const { return m_projectiles; }

private:
	virtual void updateAttack1(const int currentPlayerAnimationFrame);
	virtual void updateAttack2(const int currentPlayerAnimationFrame);
	virtual void updateAirAttack(const int currentPlayerAnimationFrame);
	virtual void updateUltimate(const int currentPlayerAnimationFrame);

	virtual void attack(Player& enemy);

	std::vector<std::unique_ptr<Projectile>> m_projectiles{};
};
