#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount)
	: AnimatedEntity{ spriteWidth, spriteHeight, animationFramesAmount }
	, ColliderEntity{ shapeWidth, shapeHeight }
{
	setSpriteTexture("skeletonIdle", "./SkeletonIdle.png");
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, constants::skeletonSpriteWidth, constants::skeletonSpriteHeight });
	setShapeSettings(sf::Vector2f{ constants::skeletonFirstPositionX, constants::skeletonFirstPositionY });
	setSpriteSettings(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f}, sf::Vector2f{ constants::skeletonSpriteScale, constants::skeletonSpriteScale });
}

void Enemy::update(float& deltaTime)
{
	updateMovement(deltaTime);

	m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f + 10.f} );
}

void Enemy::updateMovement(float& deltaTime)
{
	m_velocity.x = 0.f;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
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
	}*/

	m_sprite.setScale(m_spriteScale.x * m_facingRight, m_spriteScale.y);

	m_velocity.y += constants::gravity * deltaTime;


	/*m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f - 10.f});*/
}

void Enemy::updateTexture()
{
	/*if (m_velocity.y < 0.f)
	{
		changeCurrentTexture(constants::playerJumpingAnimationFramesAmount, "playerJumping", "./_Jump.png");
	}
	else if (m_velocity.y > 0.f)
	{
		changeCurrentTexture(constants::playerFallingAnimationFramesAmount, "playerFalling", "./_Fall.png");
	}
	else if (!m_isAttacking)
	{
		if (m_isRunning)
		{
			changeCurrentTexture(constants::playerRunningAnimationFramesAmount, "playerRunning", "./_Run.png");
		}
		else
		{
			changeCurrentTexture(constants::playerIdleAnimationFramesAmount, "playerIdle", "./_Idle.png");
		}
	}
	else
	{
		if (m_previousAttackingAnimation == "playerAttacking1")
		{
			changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "playerAttacking2", "./_Attack2NoMovement.png");
		}
		else
		{
			changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "playerAttacking1", "./_AttackNoMovement.png");
		}
	}*/
}

void Enemy::updateTextureAndAnimation()
{
	updateTexture();
	updateAnimation();
}

void Enemy::changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath)
{
	if (m_currentTexture != textureName)
	{
		m_currentAnimationFramesAmount = animationFramesAmount;
		m_frameCount = 0;
		setSpriteTexture(textureName, texturePath);
	}
}
