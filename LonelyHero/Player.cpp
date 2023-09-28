#include "Player.h"
#include "Game.h"

Player::Player(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, float spriteScale, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath)
	: AnimatedEntity{ spriteWidth, spriteHeight, animationFramesAmount, spriteScale }
	, ColliderEntity{ shapeWidth, shapeHeight, firstPosition }
{
	setSpriteTexture(textureName, texturePath);
}

void Player::update(float& deltaTime)
{
	updateMovement(deltaTime);
	updateAttack();

	if (m_isAttacking)
	{
		m_velocity.x = 0.f;
	}

	if ((m_currentTexture == "playerAttacking2" && m_frameCount >= 5) || (m_currentTexture == "playerAttacking1" && m_frameCount >= 3))
	{
		m_previousAttackingAnimation = m_currentTexture;
		m_isAttacking = false;
	}

	m_shape.move(m_velocity* deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f - 10.f});
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

	m_sprite.setScale(m_spriteScale * m_facingRight, m_spriteScale);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && m_canJump)
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * constants::gravity * constants::playerJumpSpeed);
	}

	if (!m_canJump)
	{
		m_velocity.y += constants::gravity * deltaTime;
	}


	/*m_shape.move(m_velocity * deltaTime);
	m_sprite.setPosition(sf::Vector2f{ getPosition().x + m_facingRight * (getSize().x / 2.f), getPosition().y - getSize().y / 2.f - 10.f});*/
}

void Player::updateTexture()
{
	if (m_velocity.y < 0.f)
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
	}
}

void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z) && m_velocity.y == 0.f)
	{
		m_isAttacking = true;
	}
}

void Player::updateTextureAndAnimation()
{
	updateTexture();
	updateAnimation();
}

void Player::checkIfCanJump()
{
	if (m_collisionDirection.y > 0.f)
	{
		m_canJump = true;
	}
}

void Player::changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath)
{
	if (m_currentTexture != textureName)
	{
		m_currentAnimationFramesAmount = animationFramesAmount;
		m_frameCount = 0;
		setSpriteTexture(textureName, texturePath);
	}
}
