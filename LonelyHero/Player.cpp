#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: AttackEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
	m_texturesActionName.emplace("Death", "playerDeath");
	m_texturesActionName.emplace("Hitted", "playerHitted");
	m_texturesActionName.emplace("Falling", "playerFalling");
	m_texturesActionName.emplace("Jumping", "playerJumping");
	m_texturesActionName.emplace("Running", "playerRunning");
	m_texturesActionName.emplace("Idle", "playerIdle");
	m_texturesActionName.emplace("Attacking1", "playerAttacking1");
	m_texturesActionName.emplace("Attacking2", "playerAttacking2");

	m_texturesNamePath.emplace(m_texturesActionName.at("Death"), "./assets/player/_DeathNoMovement.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Hitted"), "./assets/player/_HitSpriteSheet.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Falling"), "./assets/player/_Fall.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Jumping"), "./assets/player/_Jump.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Running"), "./assets/player/_Run.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Idle"), "./assets/player/_Idle.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking1"), "./assets/player/_AttackNoMovement.png");
	m_texturesNamePath.emplace(m_texturesActionName.at("Attacking2"), "./assets/player/_Attack2NoMovement.png");
}

void Player::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_currentTexture == "playerDeath" && m_frameCount >= 9)
	{
		dead = true;
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	if (!dead && m_currentTexture != "playerDeath")
	{
		//updateMovement(deltaTime);
		updateMovement(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right), sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up), deltaTime);
		updateAttack();
		
		move(deltaTime);

		updateTakeDamage("player");
	}
}

void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z) && m_canJump && !m_isAttacking)
	{
		m_isAttacking = true;
	}

	if (m_isAttacking)
	{
		handleAttack("player");
	}

	updateHitbox("player");
}

void Player::updateTexture()
{
	if (hp <= 0)
	{
		changeCurrentTexture(10, "playerDeath", m_texturesNamePath.at("playerDeath"));
	}
	else if (hitAltTemp)
	{
		changeCurrentTexture(constants::knightHitAnimationFramesAmount, "playerHitted", m_texturesNamePath.at("playerHitted"));
	}
	else if (m_velocity.y != 0.f && !m_canJump)
	{
		m_velocity.y > 0.f ? changeCurrentTexture(constants::knightFallingAnimationFramesAmount, "playerFalling", m_texturesNamePath.at("playerFalling")) : changeCurrentTexture(constants::knightJumpingAnimationFramesAmount, "playerJumping", m_texturesNamePath.at("playerJumping"));;
	}
	else if (!m_isAttacking)
	{
		m_isRunning ? changeCurrentTexture(constants::knightRunningAnimationFramesAmount, "playerRunning", m_texturesNamePath.at("playerRunning")) : changeCurrentTexture(constants::knightIdleAnimationFramesAmount, "playerIdle", m_texturesNamePath.at("playerIdle"));
	}
	else if (m_isAttacking)
	{
		m_previousAttackingAnimation == "playerAttacking1" ? changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "playerAttacking2", m_texturesNamePath.at("playerAttacking2")) : changeCurrentTexture(constants::knightAttacking2AnimationFramesAmount, "playerAttacking1", m_texturesNamePath.at("playerAttacking1"));
	}
}