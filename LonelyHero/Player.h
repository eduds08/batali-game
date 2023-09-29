#pragma once

#include "AttackEntity.h"
#include "Constants.h"

class Player : public AttackEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~Player() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);

	void checkIfCanJump();

	virtual void updateTexture();

private:
	bool m_canJump{ false };
};
