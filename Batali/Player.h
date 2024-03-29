#pragma once

#include "IDrawingComponent.h"
#include "IAnimatingComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"

#include "World.h"

class Player
{
public:
	Player(IDrawingComponent* drawing = nullptr, IAnimatingComponent* animating = nullptr, ICollisionComponent* physics = nullptr, IPhysicsComponent* collider = nullptr);
	virtual ~Player();

	void update(sf::RenderWindow& window, World& world, float& deltaTime);

	sf::Sprite& getSprite() { return m_sprite; }
	sf::RectangleShape& getShape() { return m_shape; }

	sf::Vector2f& getVelocity() { return m_velocity; }

private:
	IDrawingComponent* m_drawingComponent{ nullptr };
	IAnimatingComponent* m_animatingComponent{ nullptr };
	ICollisionComponent* m_collisionComponent{ nullptr };
	IPhysicsComponent* m_physicsComponent{ nullptr };

	sf::Sprite m_sprite{};
	sf::RectangleShape m_shape{};

	sf::Vector2f m_velocity{};
};
