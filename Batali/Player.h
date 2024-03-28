#pragma once

#include "IDrawingComponent.h"
#include "IAnimatingComponent.h"
#include "IPhysicsComponent.h"
#include "IMovingComponent.h"
#include "IColliderComponent.h"

#include "World.h"

class Player
{
public:
	Player(IDrawingComponent* drawing = nullptr, IAnimatingComponent* animating = nullptr, IPhysicsComponent* physics = nullptr, IMovingComponent* moving = nullptr, IColliderComponent* collider = nullptr);
	virtual ~Player();

	void update(sf::RenderWindow& window, World& world, float& deltaTime);

	sf::RectangleShape& getShape() { return m_shape; }

private:
	IDrawingComponent* m_drawingComponent{ nullptr };
	IAnimatingComponent* m_animatingComponent{ nullptr };
	IPhysicsComponent* m_physicsComponent{ nullptr };
	IMovingComponent* m_movingComponent{ nullptr };
	IColliderComponent* m_colliderComponent{ nullptr };

	sf::Sprite m_sprite{};
	sf::RectangleShape m_shape{};

	sf::Vector2f m_velocity{};
};
