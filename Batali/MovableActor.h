#pragma once

#include "ShapeActor.h"

class MovableActor : public ShapeActor
{
public:
	MovableActor();
	virtual ~MovableActor() = default;

	// Moves the shape and updates the sprite position to the same place
	void move(float& deltaTime, float offsetPositionY = 0.f);

	// MovableActor flip based on m_facingRight
	void flipSprite() { m_sprite.setScale(static_cast<float>(m_facingRight), 1.f); }

	/* Setters */

	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }

	friend class CharacterState;

protected:
	sf::Vector2f m_velocity{};

	float m_speed{};

	int m_facingRight{ 1 };
};
