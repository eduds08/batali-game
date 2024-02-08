#include "Player.h"

Player::Player(sf::Vector2f firstPosition, const std::string& chosenCharacter, int playerNumber)
	: SwordEntity{ firstPosition }
	, m_chosenCharacter{ chosenCharacter }
	, m_playerNumber{ playerNumber }
{
	if (m_chosenCharacter == "FIRE_KNIGHT")
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
		m_airAttackingStartingFrame = 3;
		m_airAttackingEndingFrame = 5;

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
	else if (m_chosenCharacter == "WIND_HASHASHIN")
	{
		//m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack1;
		m_hitboxHeight = constants::windHashashinSwordHitboxHeight;
		//m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);

		m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
		m_attackHitbox.setOutlineThickness(1.f);

		// Initialize starting/ending attackings' frames
		m_attack1StartingFrame = 0;
		m_attack1EndingFrame = 4;
		m_attack2StartingFrame = 1;
		m_attack2EndingFrame = 7;

		m_entityName = "enemy";
		initTexturesMap();

		// Initialize sprite
		m_spriteWidth = constants::windHashashinSpriteWidth;
		m_spriteHeight = constants::windHashashinSpriteHeight;
		m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle"))));
		m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

		// Initialize shape
		m_shape.setSize(sf::Vector2f{ constants::windHashashinShapeWidth, constants::windHashashinShapeHeight});
		m_shape.setOrigin(m_shape.getSize() / 2.f);
		m_shape.setPosition(firstPosition.x, firstPosition.y);
		m_shape.setOutlineColor(sf::Color::Red);
		m_shape.setOutlineThickness(1.f);

		// Initialize other attributes
		m_jumpHeight = constants::enemyJumpHeight;
		m_hp = constants::enemyHp;

		// Initialize other attributes
		m_speed = 260.f;
	}
}

void Player::update(float& deltaTime)
{
	updateDeath();

	// Only called if hp > 0
	if (!m_dying)
	{
		bool conditionAttack = false;

		if (m_playerNumber == 1)
		{
			bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);
			bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right);
			bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);

			updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime, sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::NumpadEnter));

			conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Numpad0);
		}
		else if (m_playerNumber == 2)
		{
			bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
			bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);
			bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);

			updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime, sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C));

			conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift);
		}

		if (m_chosenCharacter == "FIRE_KNIGHT")
		{
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
			else if (m_currentTexture == "playerAirAttacking")
			{
				m_hitboxWidth = constants::fireKnightSwordHitboxWidthAirAttacking;
				m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight * 3 } / 2.f);
			}
		}
		else if (m_chosenCharacter == "WIND_HASHASHIN")
		{
			if (m_currentTexture == "enemyAttacking1")
			{
				m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack1;
				m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
			}
			else if (m_currentTexture == "enemyAttacking2")
			{
				m_hitboxWidth = constants::windHashashinSwordHitboxWidthAttack2;
				m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);
			}
		}
		
		updateAttack(conditionAttack);

		if (m_chosenCharacter == "FIRE_KNIGHT")
		{
			if (m_currentTexture == "playerAttacking1")
			{
				m_damage = 100;
			}
			else if (m_currentTexture == "playerAttacking2")
			{
				m_damage = 70;
			}
			else if (m_currentTexture == "playerAirAttacking")
			{
				m_damage = 80;
			}
		}
		else if (m_chosenCharacter == "WIND_HASHASHIN")
		{
			if (m_currentTexture == "enemyAttacking1")
			{
				m_damage = 150;
			}
			else if (m_currentTexture == "enemyAttacking2")
			{
				m_damage = 90;
			}
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
	if (m_chosenCharacter == "FIRE_KNIGHT")
	{
		if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) ||
			(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame) ||
			(m_currentTexture == m_entityName + "AirAttacking" && m_frameCount > m_airAttackingStartingFrame && m_frameCount < m_airAttackingEndingFrame))
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
	else if (m_chosenCharacter == "WIND_HASHASHIN")
	{
		if ((m_currentTexture == m_entityName + "Attacking1" && m_frameCount > m_attack1StartingFrame && m_frameCount < m_attack1EndingFrame) ||
			(m_currentTexture == m_entityName + "Attacking2" && m_frameCount > m_attack2StartingFrame && m_frameCount < m_attack2EndingFrame))
		{
			m_attackHitbox.setSize(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight });
			m_attackHitbox.setPosition(getPosition() + sf::Vector2f(m_facingRight * m_attackHitbox.getSize().x / 2.f, 0.f));
		}
		else
		{
			m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
			m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		}
	}
}
