#pragma once

#include "AnimatedEntity.h"
#include "Ground.h"

class Player : public AnimatedEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~Player() = default;

	void move(float& deltaTime);

	void update(float& deltaTime);
	void updateTexture();


	void setCanJump(bool canJump) { m_canJump = canJump; }

	
	void onCollision(float directionX, float directionY);

	float collisionDirectionX{ 0.f };
	float collisionDirectionY{ 0.f };

	void moveTmp(float x, float y) { m_shape.move(x, y); }

private:
	bool m_canJump{ false };

	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };
};
