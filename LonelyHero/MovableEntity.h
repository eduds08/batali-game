#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class MovableEntity : public AnimatedEntity, public ColliderEntity
{
public:
	MovableEntity(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, float spriteScale = 1.f);
	virtual ~MovableEntity() = default;

	void handleCollision();

	void move(float yAxisAdjustment, float& deltaTime);

protected:

	sf::Vector2f m_velocity{};

	bool m_isRunning{ false };
	int m_facingRight{ 1 };
};

