#pragma once

#include "Projectile.h"

class BoxerUltimateProjectile : public Projectile
{
public:
	BoxerUltimateProjectile(sf::Vector2f firstPosition, float direction);
	virtual ~BoxerUltimateProjectile() = default;
};
