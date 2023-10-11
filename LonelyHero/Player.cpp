#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
}

void Player::update(float& deltaTime)
{
	if (!dead)
	{
		updateMovement(deltaTime);
		updateAttack();
		
		move(m_spriteHeight - m_shape.getSize().y, deltaTime);
	}
}

void Player::updateMovement(float& deltaTime)
{
	m_velocity.x = 0.f;
	m_isRunning = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		m_facingRight = -1;
		m_velocity.x -= constants::playerSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		m_facingRight = 1;
		m_velocity.x += constants::playerSpeed;
	}
	else
	{
		m_isRunning = false;
	}

	flipSprite();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && m_canJump && !m_isAttacking)
	{
		m_canJump = false;
		m_velocity.y = -1 * sqrt(2.f * constants::gravity * constants::playerJumpSpeed);
	}

	m_velocity.y += constants::gravity * deltaTime;
}

void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z) && m_canJump && !m_isAttacking)
	{
		m_isAttacking = true;
	}

	if (m_isAttacking)
	{
		handleAttack("knight");
	}

	updateHitbox("knight");
}

void Player::updateTexture()
{
	if (m_velocity.y != 0.f && !m_canJump)
	{
		m_velocity.y > 0.f ? changeCurrentTexture(constants::knightFallingAnimationFramesAmount, "knightFalling", "./_Fall.png") : changeCurrentTexture(constants::knightJumpingAnimationFramesAmount, "knightJumping", "./_Jump.png");;
	}
	else if (!m_isAttacking)
	{
		m_isRunning ? changeCurrentTexture(constants::knightRunningAnimationFramesAmount, "knightRunning", "./_Run.png") : changeCurrentTexture(constants::knightIdleAnimationFramesAmount, "knightIdle", "./_Idle.png");
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == "knightAttacking1" ? changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "knightAttacking2", "./_Attack2NoMovement.png") : changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "knightAttacking1", "./_AttackNoMovement.png");
	}
}
