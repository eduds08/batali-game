#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"

class Player : public AnimatedEntity, public ColliderEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~Player() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	void updateTexture();

	void setCanJump(bool canJump) { m_canJump = canJump; }

private:
	bool m_canJump{ false };
	bool m_isRunning{ false };
	int m_facingRight{ 1 };
};
