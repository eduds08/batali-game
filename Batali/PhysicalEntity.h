#pragma once

#include "AnimatedEntity.h"

class PhysicalEntity : public AnimatedEntity
{
public:
	PhysicalEntity();
	virtual ~PhysicalEntity() = default;

	const sf::RectangleShape& getShape() const { return m_shape; }
	const sf::Vector2f& getShapeSize() const { return m_shape.getSize(); }
	const sf::Vector2f& getShapePosition() const { return m_shape.getPosition(); }

	void setShapePosition(sf::Vector2f position) { m_shape.setPosition(position); }

	// Sets the values of the imaginary view of an entity. Useful to call isCollidingWith() with less tiles (only the ones inside the limits)
	void updateLimits();

	float m_rightShapeLimit{};
	float m_leftShapeLimit{};
	float m_topShapeLimit{};
	float m_bottomShapeLimit{};

protected:
	sf::RectangleShape m_shape{};
};
