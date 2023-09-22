#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"

class Player : public AnimatedEntity, public ColliderEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~Player() = default;

	void move(float& deltaTime);

	void update(float& deltaTime);
	void updateTexture();

	void setCanJump(bool canJump) { m_canJump = canJump; }

	sf::Vector2f& getVelocity() { return m_velocity; }

private:
	bool m_canJump{ false };

	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	sf::Vector2f m_velocity{};
	
};
