#pragma once

#include "SFML/Graphics.hpp"]

class SwordHitbox
{
public:
	SwordHitbox();
	~SwordHitbox();

	void setPosition(const sf::Vector2f& entityPosition) { m_shape.setPosition(entityPosition); }

	const sf::RectangleShape& const getShape() { return m_shape; }

private:
	sf::RectangleShape m_shape{};
};

