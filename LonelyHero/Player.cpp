#include "Player.h"

Player::Player(sf::Vector2f firstPosition)
	: SwordEntity{ firstPosition }
{
	m_hitboxWidth = constants::fireKnightSwordHitboxWidth;
	m_hitboxHeight = constants::fireKnightSwordHitboxHeight;
	m_attackHitbox.setOrigin(sf::Vector2f{ m_hitboxWidth, m_hitboxHeight } / 2.f);

	m_attackHitbox.setFillColor(sf::Color{255, 0, 0, 50});
	m_attackHitbox.setOutlineThickness(1.f);

	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 4;
	m_attack1EndingFrame = 7;
	m_attack2StartingFrame = 3;
	m_attack2EndingFrame = 7;

	m_entityName = "player";
	initTexturesMap();

	// Initialize sprite
	m_spriteWidth = constants::fireKnightSpriteWidth;
	m_spriteHeight = constants::fireKnightSpriteHeight;
	m_spriteScale = constants::fireKnightSpriteScale;
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture(m_texturesActionName.at("Idle"), m_texturesNamePath.at(m_texturesActionName.at("Idle"))));
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
		bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);
		bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right);
		bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);

		updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime);

		bool conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z);

		updateAttack(conditionAttack);

		if (m_currentTexture == "playerAttacking1")
		{
			m_damage = 100;
		}
		else if (m_currentTexture == "playerAttacking2")
		{
			m_damage = 50;
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
