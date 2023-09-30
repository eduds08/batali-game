#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class MovableEntity : public AnimatedEntity, public ColliderEntity
{
public:
	MovableEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~MovableEntity() = default;

	void handleCollision();

	void move(float yAxisAdjustment, float& deltaTime);

protected:

	sf::Vector2f m_velocity{};

	bool m_isRunning{ false };
	int m_facingRight{ 1 };
};
