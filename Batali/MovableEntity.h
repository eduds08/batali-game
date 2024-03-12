#pragma once

#include "PhysicalEntity.h"

class MovableEntity : public PhysicalEntity
{
public:
	MovableEntity();
	virtual ~MovableEntity() = default;

	// Moves the shape and updates the sprite position to the same place
	void move(float& deltaTime);

	// MovableEntity flip based on m_facingRight
	void flipSprite() { m_sprite.setScale(static_cast<float>(m_facingRight), 1.f); }

	/* Setters */

	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	
protected:
	sf::Vector2f m_velocity{};
	float m_speed{};

	int m_facingRight{ 1 };
};
