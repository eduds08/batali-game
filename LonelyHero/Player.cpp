#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime)
	: AnimatedEntity{spriteWidth, spriteHeight, animationFramesAmount, animationSwitchTime}
	, ColliderEntity{shapeWidth, shapeHeight}
{
	setSpriteTexture("playerIdle", "./_Idle.png");
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 120, 80 });
	setShapeSettings(sf::Vector2f{ 300.f, 0.f });
	setSpriteSettings(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f}, sf::Vector2f{ 2.f, 2.f });
}

void Player::update(float& deltaTime)
{
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
		m_velocity.x -= 240.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		m_isRunning = true;
		m_facingRight = 1;
		m_velocity.x += 240.f;
	}
	else
	{
		m_isRunning = false;
	}

	m_sprite.setScale(m_spriteScale.x * m_facingRight, m_spriteScale.y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && m_canJump)
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * 981.f * 200.f);
	}

	m_velocity.y += 981.f * 1.5f * deltaTime;

	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f});
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
