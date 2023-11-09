#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f firstPosition)
	: SwordEntity{ firstPosition }
{
	//m_hitboxWidth = constants::fireKnightSwordHitboxWidthAttack1;
	m_hitboxHeight = constants::fireKnightSwordHitboxHeight;
	//m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);

	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 4;
	m_attack1EndingFrame = 7;
	m_attack2StartingFrame = 1;
	m_attack2EndingFrame = 7;

	m_entityName = "player";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = constants::fireKnightSpriteWidth;
	m_spriteHeight = constants::fireKnightSpriteHeight;
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle"))));
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::fireKnightShapeWidth, constants::fireKnightShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_speed = constants::playerSpeed;
	m_jumpHeight = constants::playerJumpHeight;
	m_hp = constants::playerHp;
}

void Player::update(float& deltaTime)
{
	updateDeath();

	// Only called if hp > 0
	if (!m_dying)
	{
		bool conditionRunLeft = ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -60) && (sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= -100)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);
		bool conditionRunRight = ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 60) && (sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= 100)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right);
		bool conditionJump = sf::Joystick::isButtonPressed(0, 1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);

		updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime, sf::Joystick::isButtonPressed(0, 2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X));

		bool conditionAttack = sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z);

		if (m_currentTexture == "playerAttacking1")
		{
			m_hitboxWidth = constants::fireKnightSwordHitboxWidthAttack1;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}
		else if (m_currentTexture == "playerAttacking2")
		{
			m_hitboxWidth = constants::fireKnightSwordHitboxWidthAttack2;
			m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
		}

		updateAttack(conditionAttack);

		if (m_currentTexture == "playerAttacking1")
		{
			m_damage = 100;
		}
		else if (m_currentTexture == "playerAttacking2")
		{
			m_damage = 70;
		}

		updateDamage();

		move(deltaTime);
	}

	if (!m_dead)
	{
		updateGravityWhenDying(deltaTime);
		updateLimits();
	}
}

void Player::updateHitbox()
{
	if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) || (m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame))
	{
		m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
		if (m_currentTexture == "playerAttacking2")
		{
			m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * 10.f / 2.f, 0.f));
		}
		else
		{
			m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
		}
	}
	else
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
}
