#include "Player.h"
#include <iostream>

Player::Player(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime)
	: AnimatedEntity(frameWidth, frameHeight, frameAmount, switchAnimationTime)
{
	setSpriteTexture("playerIdle", "./_Idle.png");
	setSpriteSettings(300.f, 0.f, 2.f, 2.f);
}

void Player::move(float& deltaTime)
{
	m_velocityX = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		m_isRunning = true;
		m_facingRight = -1;
		m_velocityX -= 240.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		m_isRunning = true;
		m_facingRight = 1;
		m_velocityX += 240.f;
	}
	else
	{
		m_isRunning = false;
	}

	m_sprite.setScale(2.f * m_facingRight, 2.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && m_canJump)
	{
		m_canJump = false;
		m_velocityY =  -1 * sqrt(2.f * 981.f * 200.f);
	}

	m_velocityY += 981.f * 1.5f * deltaTime;

	if (collisionDirectionY != 0.f)
	{
		m_velocityY = 0.f;
	}

	m_sprite.move(m_velocityX * deltaTime, m_velocityY * deltaTime);
}

void Player::update(float& deltaTime)
{
	move(deltaTime);
	updateTexture();
	updateAnimation(deltaTime);
}

void Player::updateTexture()
{
	if (m_isRunning)
	{
		if (m_currentSprite == "playerIdle")
		{
			m_frameCount = 0;
			setSpriteTexture("playerRunning", "./_Run.png");
		}
	}
	else
	{
		if (m_currentSprite == "playerRunning")
		{
			m_frameCount = 0;
			setSpriteTexture("playerIdle", "./_Idle.png");
		}
	}
}