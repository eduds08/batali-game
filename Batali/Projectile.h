#pragma once

#include "MovableEntity.h"

class Projectile : public MovableEntity
{
public:
	Projectile(sf::Vector2f firstPosition, float direction, const std::string& entityName);
	virtual ~Projectile() = default;

	void update(float& deltaTime);

	void updateTexture();

	/* SETTERS */

	void setCollided(bool collided) { m_collided = collided; }

	/* GETTERS */
	
	const bool getCollided() const { return m_collided; }
	const bool getVanished() const { return m_vanished; }

private:
	bool m_collided{ false };
	bool m_vanished{ false };

};
