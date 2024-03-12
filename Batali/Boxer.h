#pragma once

#include "ProjectileEntity.h"

class Boxer : public ProjectileEntity
{
public:
	Boxer(sf::Vector2f firstPosition);
	virtual ~Boxer() = default;

	virtual void updateAttackHitbox();

	void launchUltimate();

	std::vector<std::shared_ptr<Projectile>> m_ultimateProjectiles{};

private:
	
};
