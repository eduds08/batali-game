#pragma once

#include "AnimatedEntity.h"

class Player : public AnimatedEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~Player() = default;

	void move(float& deltaTime);

	void update(float& deltaTime);
	void updateTexture();

	bool isColliding(sf::RectangleShape& shape);


	void setCanJump(bool canJump) { m_canJump = canJump; }

	void onCollision();

private:
	bool m_canJump{ false };

	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };

	sf::Vector2f m_collisionDirection{};
};
