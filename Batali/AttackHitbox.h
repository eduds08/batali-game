#pragma once

#include "SFML/Graphics.hpp"

class AttackHitbox
{
public:
	AttackHitbox();
	virtual ~AttackHitbox() = default;

	void setShapeSize(const sf::Vector2f& size) { m_shape.setSize(size); }
	void setShapeSize(float sizeX, float sizeY) { m_shape.setSize(sf::Vector2f{ sizeX, sizeY }); }

	void setShapePosition(const sf::Vector2f& position) { m_shape.setPosition(position); }

	void setShapeOrigin(float originX, float originY) { m_shape.setOrigin(originX, originY); }

	void setShapeScale(float scaleX, float scaleY) { m_shape.setScale(scaleX, scaleY); }

	const sf::Vector2f& getShapeSize() const { return m_shape.getSize(); }

	void reset();

	void setDamage(int damage) { m_damage = damage; }

private:
	sf::RectangleShape m_shape{ sf::Vector2f{0.f, 0.f} };

	int m_damage{};
};
