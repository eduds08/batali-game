#include "Player.h"

Player::Player(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime)
	: AnimatedEntity(frameWidth, frameHeight, frameAmount, switchAnimationTime)
{
	setSpriteTexture("playerIdle", "./_Idle.png");
	setSpriteSettings(300.f, 0.f, 2.f, 2.f);
}

Player::~Player()
{
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && canJump)
	{
		canJump = false;
		m_velocityY =  -1 * sqrt(2.f * 981.f * 200.f);
	}

	m_velocityY += 981.f * 1.5f * deltaTime;

	m_sprite.move(m_velocityX * deltaTime, m_velocityY * deltaTime);
	if (m_sprite.getPosition().y > 460.f)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, 460.1f);
	}
}

void Player::update(float& deltaTime)
{
	move(deltaTime);
	updateTexture();
	m_sprite.setScale(2.f * m_facingRight, 2.f);
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

void Player::checkCollisionWith(sf::FloatRect bounds)
{
	if (getBounds().intersects(bounds))
	{
		canJump = true;
	}
}
