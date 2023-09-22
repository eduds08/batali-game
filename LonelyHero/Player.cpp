#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime)
	: AnimatedEntity{ spriteWidth, spriteHeight, animationFramesAmount, animationSwitchTime }
	, ColliderEntity{ shapeWidth, shapeHeight }
{
	setSpriteTexture("playerIdle", "./_Idle.png");
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, constants::playerSpriteWidth, constants::playerSpriteHeight });
	setShapeSettings(sf::Vector2f{ constants::playerFirstPositionX, constants::playerFirstPositionY });
	setSpriteSettings(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f}, sf::Vector2f{ constants::playerSpriteScale, constants::playerSpriteScale });
}

void Player::update(float& deltaTime)
{
	if (m_velocity.y < 0.f)
	{
		m_isJumping = true;
		m_isFalling = false;
	}
	else if (m_velocity.y > 0.f)
	{
		m_isJumping = false;
		m_isFalling = true;
	}
	else
	{
		m_isJumping = false;
		m_isFalling = false;
	}
	updateTexture();
	updateAnimation(deltaTime);
	updateMovement(deltaTime);

	
}

void Player::updateMovement(float& deltaTime)
{
	m_velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		m_isRunning = true;
		m_facingRight = -1;
		m_velocity.x -= constants::playerSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		m_isRunning = true;
		m_facingRight = 1;
		m_velocity.x += constants::playerSpeed;
	}
	else
	{
		m_isRunning = false;
	}

	m_sprite.setScale(m_spriteScale.x * m_facingRight, m_spriteScale.y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && m_canJump)
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * constants::gravity * constants::playerJumpSpeed);
	}

	m_velocity.y += constants::gravity * deltaTime;

	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f});
}

void Player::updateTexture()
{
	if (m_isRunning && !m_isJumping && !m_isFalling)
	{
		if (m_currentSprite != "playerRunning")
		{
			m_currentAnimationFramesAmount = constants::playerIdleAnimationFramesAmount;
			m_frameCount = 0;
			setSpriteTexture("playerRunning", "./_Run.png");
		}
	}
	else if (!m_isRunning && !m_isJumping && !m_isFalling)
	{
		if (m_currentSprite != "playerIdle")
		{
			m_currentAnimationFramesAmount = constants::playerRunningAnimationFramesAmount;
			m_frameCount = 0;
			setSpriteTexture("playerIdle", "./_Idle.png");
		}
	}
	else if (m_isJumping)
	{
		if (m_currentSprite != "playerJumping")
		{
			m_currentAnimationFramesAmount = constants::playerJumpingAnimationFramesAmount;
			m_frameCount = 0;
			setSpriteTexture("playerJumping", "./_Jump.png");
		}
	}
	else if (!m_isJumping && m_isFalling)
	{
		if (m_currentSprite != "playerFalling")
		{
			m_currentAnimationFramesAmount = constants::playerFallingAnimationFramesAmount;
			m_frameCount = 0;
			setSpriteTexture("playerFalling", "./_Fall.png");
		}
	}
}

void Player::checkIfCanJump()
{
	if (m_collisionDirection.y > 0.f)
	{
		m_canJump = true;
	}
}
