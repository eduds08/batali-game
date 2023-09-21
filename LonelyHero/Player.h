#pragma once

#include "AnimatedEntity.h"

class Player : public AnimatedEntity
{
public:
	Player(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime);
	~Player();

	void move(float& deltaTime);

	void update(float& deltaTime);
	void updateTexture();

	void checkCollisionWith(sf::FloatRect bounds);

private:

	bool canJump{ false };

	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	bool m_isJumping{ false };

	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };
};
