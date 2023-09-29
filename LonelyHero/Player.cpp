#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
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
	m_canJump = m_collisionDirection.y > 0.f;
}

void Player::updateTexture()
{
	if (m_velocity.y != 0.f)
	{
		m_velocity.y > 0.f ? changeCurrentTexture(constants::playerFallingAnimationFramesAmount, "playerFalling", "./_Fall.png") : changeCurrentTexture(constants::playerJumpingAnimationFramesAmount, "playerJumping", "./_Jump.png");;
	}
	else if (!m_isAttacking)
	{
		m_isRunning ? changeCurrentTexture(constants::playerRunningAnimationFramesAmount, "playerRunning", "./_Run.png") : changeCurrentTexture(constants::playerIdleAnimationFramesAmount, "playerIdle", "./_Idle.png");
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == "playerAttacking1" ? changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "playerAttacking2", "./_Attack2NoMovement.png") : changeCurrentTexture(constants::playerAttacking2AnimationFramesAmount, "playerAttacking1", "./_AttackNoMovement.png");
	}
}
