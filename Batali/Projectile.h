#pragma once

#include "MovableEntity.h"

class Projectile : public MovableEntity
{
public:
	Projectile(sf::Vector2f firstPosition, float direction);
	virtual ~Projectile() = default;

	void updateTexture();

	void update(float& deltaTime);

	bool m_collided{ false };
	bool m_vanished{ false };
private:
	

};
