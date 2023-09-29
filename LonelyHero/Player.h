#pragma once

#include "AttackEntity.h"
#include "Constants.h"

class Player : public AttackEntity
{
public:
	Player(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath, float spriteScale = 1.f);
	virtual ~Player() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);

	void checkIfCanJump();

	virtual void updateTexture();

private:
	bool m_canJump{ false };
};
