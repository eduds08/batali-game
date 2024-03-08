#pragma once

#include "AnimatedEntity.h"

class Projectile : public AnimatedEntity
{
public:
	Projectile(sf::Vector2f firstPosition, float direction);
	virtual ~Projectile() = default;

	void updateTexture();

	void update(float& deltaTime);
private:
	bool m_collided{ false };

};
