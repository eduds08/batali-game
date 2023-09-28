#pragma once

#include "SFML/Graphics.hpp"

class ColliderEntity
{
public:
	ColliderEntity(float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~ColliderEntity() = default;

	bool isColliding(const sf::RectangleShape& shape);
	bool isColliding(const sf::Sprite& sprite);

	void handleCollision();

	const sf::RectangleShape& getShape() const { return m_shape; }

	const sf::Vector2f& getSize() const { return m_shape.getSize(); }
	const sf::Vector2f& getPosition() const { return m_shape.getPosition(); }

	void setShapeSettings(sf::Vector2f position);

	const sf::Vector2f& getCollisionDirection() const { return m_collisionDirection; }

	const sf::Vector2f& getVelocity() const { return m_velocity; }

protected:
	sf::RectangleShape m_shape{};

	sf::Vector2f m_collisionDirection{};
	sf::Vector2f m_velocity{};

	float m_shapeWidth{};
	float m_shapeHeight{};
};
