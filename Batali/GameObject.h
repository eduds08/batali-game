#pragma once

#include "World.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	virtual void update(sf::RenderWindow& window, World& world, float& deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	sf::Sprite& getSprite() { return m_sprite; }

	sf::RectangleShape& getShape() { return m_shape; }

	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }
	void setVelocity(float velocityX, float velocityY) { m_velocity = sf::Vector2f{ velocityX, velocityY }; }

	sf::Vector2f& getVelocity() { return m_velocity; }

	void setFacingRight(int facingRight) { m_facingRight = facingRight; }
	const int getFacingRight() const { return m_facingRight; }

	void updateFlip() { m_sprite.setScale(static_cast<float>(m_facingRight), 1.f); }

	int getId() { return m_id; }

	virtual const std::string& getName() const = 0;

protected:
	sf::Sprite m_sprite{};
	sf::RectangleShape m_shape{};

	sf::Vector2f m_velocity{};

	int m_facingRight{ 1 };

	static int s_idCounter;
	const int m_id;
};
