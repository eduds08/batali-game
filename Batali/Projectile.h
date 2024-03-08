#pragma once

#include "AnimatedEntity.h"

class Projectile : public AnimatedEntity
{
public:
	Projectile(sf::Vector2f firstPosition);
	virtual ~Projectile() = default;

	void updateTexture();
private:
	bool m_collided{ false };

};
