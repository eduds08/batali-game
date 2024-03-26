#pragma once

#include "MovableEntity.h"

class Projectile : public MovableEntity
{
public:
	Projectile(const std::string& entityName);
	virtual ~Projectile() = default;

	void update(float& deltaTime);

	virtual void updateTexture();

	/* SETTERS */

	void setCollided(bool collided) { m_collided = collided; }

	/* GETTERS */
	
	const bool getCollided() const { return m_collided; }
	const bool getVanished() const { return m_vanished; }
	const int getDamage() const { return m_damage; }

protected:
	bool m_collided{ false };
	bool m_vanished{ false };

	int m_damage{};
};
