#include "Player.h"

Player::Player(int frameWidth, int frameHeight, int frameAmount)
	: DrawableEntity(frameWidth, frameHeight, frameAmount)
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

	if (onFloor)
		m_velocityY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		m_isRunning = true;
		m_facingRight = -1;

		m_velocityX = -240.f * deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		m_isRunning = true;
		m_facingRight = 1;

		m_velocityX = 240.f * deltaTime;
	}
	else
	{
		m_isRunning = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && onFloor == true)
	{
		m_isJumping = true;
	}

	if(m_isJumping)
		m_velocityY = m_velocityY - 981.f * 0.5f * deltaTime - 10.f;

	if (!onFloor)
		m_velocityY = m_velocityY + 981.f * 0.5f * deltaTime + 11.f;

	x = m_velocityX;
	y = m_velocityY;

	if (m_sprite.getPosition().y + y > 460.1f)
	{
		m_isJumping = false;
		y = 460.1f - m_sprite.getPosition().y;
	}

	m_sprite.setPosition(m_sprite.getPosition().x + x, m_sprite.getPosition().y + y);
	//m_sprite.move(x, y);
}

void Player::update(float& deltaTime)
{
	move(deltaTime);

	if (m_isRunning)
	{
		if (m_currentSprite == "playerIdle")
		{
			m_textureFrameCount = 0;
			setSpriteTexture("playerRunning", "./_Run.png");
		}
	}
	else
	{
		if (m_currentSprite == "playerRunning")
		{
			m_textureFrameCount = 0;
			setSpriteTexture("playerIdle", "./_Idle.png");
		}
	}

	m_sprite.setScale(2.f * m_facingRight, 2.f);

	updateAnimation(deltaTime);
}

void Player::checkCollisionWith(sf::FloatRect bounds)
{
	bool interceptou = false;
	if (getBounds().intersects(bounds))
	{
		interceptou = true;
	}
	onFloor = interceptou;
}
