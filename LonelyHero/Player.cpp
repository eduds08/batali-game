#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath, float spriteScale)
	: AttackEntity{spriteWidth, spriteHeight, animationFramesAmount, shapeWidth, shapeHeight, firstPosition, spriteScale}
{
	setSpriteTexture(textureName, texturePath);
}

void Player::update(float& deltaTime)
{
	updateMovement(deltaTime);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z) && m_velocity.y == 0.f && !m_isAttacking)
	{
		m_isAttacking = true;
	}

	updateAttack("player");

	updateHitbox();

	move(18.f, deltaTime);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && m_canJump && !m_isAttacking)
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * constants::gravity * constants::playerJumpSpeed);
	}

	if (!m_canJump)
	{
		m_velocity.y += constants::gravity * deltaTime;
	}
}

void Player::checkIfCanJump()
{
	if (m_collisionDirection.y > 0.f)
	{
		m_canJump = true;
	}
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