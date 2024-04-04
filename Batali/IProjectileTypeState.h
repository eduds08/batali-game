#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Projectile;

class IProjectileTypeState
{
public:
	virtual ~IProjectileTypeState() = default;

	virtual const std::string& getName() const = 0;

	virtual void enter(Projectile& projectile) = 0;
};
