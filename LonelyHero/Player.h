#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"

class Player : public AnimatedEntity, public ColliderEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~Player() = default;

	void move(float& deltaTime);

	virtual void walk(float offsetX, float offsetY) { m_shape.move(offsetX, offsetY); }

	void update(float& deltaTime);
	void updateTexture();

	void setCanJump(bool canJump) { m_canJump = canJump; }

	virtual const sf::Vector2f& getPosition() const { return m_shape.getPosition(); }
	virtual const sf::Vector2f& getSize() const { return m_shape.getSize(); }

	float& getVelocityX() { return m_velocityX; }
	float& getVelocityY() { return m_velocityY; }

private:
	bool m_canJump{ false };

	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };

	
};
