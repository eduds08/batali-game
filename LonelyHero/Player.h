#pragma once

#include "DrawableEntity.h"

class Player : public DrawableEntity
{
public:
	Player(int frameWidth, int frameHeight, int frameAmount);
	~Player();

	void move(float& deltaTime);

	void update(float& deltaTime);

	bool onFloor{ false };

	void checkCollisionWith(sf::FloatRect bounds);

private:
	bool m_isRunning{ false };
	int m_facingRight{ 1 };

	bool m_isJumping{ false };

	float x{};
	float y{};

	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };
};
