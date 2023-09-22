#pragma once

#include "SFML/Graphics.hpp"

class ColliderEntity
{
public:
	ColliderEntity() {}
	virtual ~ColliderEntity() = default;

	bool isColliding(sf::RectangleShape& shape);
	//void onCollision(sf::Vector2f& velocity);
	void onCollision(float& velocityX, float& velocityY);

	virtual const sf::Vector2f& getSize() const = 0;
	virtual const sf::Vector2f& getPosition() const = 0;
	virtual void walk(float offsetX, float offsetY) = 0;

	const sf::Vector2f& getCollisionDirection() const { return m_collisionDirection; }

protected:

	sf::Vector2f m_collisionDirection{};

};
