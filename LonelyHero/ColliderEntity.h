#pragma once

#include "SFML/Graphics.hpp"

class ColliderEntity
{
public:
	ColliderEntity(float shapeWidth, float shapeHeight);
	virtual ~ColliderEntity() = default;

	bool isColliding(const sf::RectangleShape& shape);
	bool isColliding(const sf::Sprite& sprite);

	void onCollision(sf::Vector2f& velocity);

	const sf::RectangleShape& getShape() const { return m_shape; }

	const sf::Vector2f& getSize() const { return m_shape.getSize(); }
	const sf::Vector2f& getPosition() const { return m_shape.getPosition(); }

	void setShapeSettings(sf::Vector2f position);

	const sf::Vector2f& getCollisionDirection() const { return m_collisionDirection; }

protected:
	sf::RectangleShape m_shape{};

	float m_shapeWidth{};
	float m_shapeHeight{};

	sf::Vector2f m_collisionDirection{};
};
