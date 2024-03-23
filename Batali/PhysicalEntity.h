#pragma once

#include "AnimatedEntity.h"

class PhysicalEntity : public AnimatedEntity
{
public:
	PhysicalEntity();
	virtual ~PhysicalEntity() = default;
	
	// Create an imaginary rectangle around PhysicalEntity. Useful to call isCollidingWith() with less tiles (only the ones inside the imaginary rectangle).
	void updateLimits();

	/* Setters */

	void setShapePosition(const sf::Vector2f& position) { m_shape.setPosition(position); }

	/* Getters */

	const sf::RectangleShape& getShape() const { return m_shape; }
	const sf::Vector2f& getShapeSize() const { return m_shape.getSize(); }
	const sf::Vector2f& getShapePosition() const { return m_shape.getPosition(); }
	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	const std::vector<float>& getShapeLimits() const { return m_shapeLimits; }

protected:
	sf::RectangleShape m_shape{};

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	std::vector<float> m_shapeLimits{ 0.f, 0.f, 0.f, 0.f };
};
