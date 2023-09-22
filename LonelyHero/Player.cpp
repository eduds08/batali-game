#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime)
	: AnimatedEntity{spriteWidth, spriteHeight, shapeWidth, shapeHeight, animationFramesAmount, animationSwitchTime}
{
	setSpriteTexture("playerIdle", "./_Idle.png");
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 120, 80 });
	setShapeSettings(300.f, 0.f);
	setSpriteSettings();
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

	m_shape.move(m_velocityX * deltaTime, m_velocityY * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f});
}

void Player::update(float& deltaTime)
{
	updateTexture();
	updateAnimation(deltaTime);
	move(deltaTime);
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

bool Player::isColliding(sf::RectangleShape& shape)
{
	float groundHalfSizeX = shape.getSize().x / 2.f;
	float groundHalfSizeY = shape.getSize().y / 2.f;
	float groundPositionX = shape.getPosition().x;
	float groundPositionY = shape.getPosition().y;

	float playerHalfSizeX = getSize().x / 2.f;
	float playerHalfSizeY = getSize().y / 2.f;
	float playerPositionX = getPosition().x;
	float playerPositionY = getPosition().y;

	float deltaX = groundPositionX - playerPositionX;
	float deltaY = groundPositionY - playerPositionY;

	float intersectX = abs(deltaX) - (groundHalfSizeX + playerHalfSizeX);
	float intersectY = abs(deltaY) - (groundHalfSizeY + playerHalfSizeY);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		if (intersectX > intersectY) {

			if (deltaX > 0.f)
			{
				m_shape.move(intersectX, 0.f);
				m_collisionDirection.x = 1.0f;
			}
			else
			{
				m_shape.move(-intersectX, 0.f);
				m_collisionDirection.x = -1.0f;
			}
			m_collisionDirection.y = 0.f;
		}
		else
		{
			if (deltaY > 0.f)
			{
				m_shape.move(0.f, intersectY);
				m_collisionDirection.y = 1.0f;
			}
			else
			{
				m_shape.move(0.f, -intersectY);
				m_collisionDirection.y = -1.0f;
			}
			m_collisionDirection.x = 0.f;
		}

		return true;
	}

	return false;
}

void Player::onCollision()
{
	if (m_collisionDirection.x != 0.f)
	{
		m_velocityX = 0.f;
	}
	if (m_collisionDirection.y != 0.f)
	{
		m_velocityY = 0.f;
		if (m_collisionDirection.y > 0.f)
		{
			m_canJump = true;
		}
	}
}
