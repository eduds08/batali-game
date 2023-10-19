#include "Player.h"

Player::Player(sf::Vector2f firstPosition)
	: SwordEntity{ firstPosition }
{
	// Initialize starting/ending attackings' frames
	m_attack1StartingFrame = 4;
	m_attack1EndingFrame = 7;
	m_attack2StartingFrame = 3;
	m_attack2EndingFrame = 7;

	// Initialize sprite
	m_spriteWidth = constants::knightSpriteWidth;
	m_spriteHeight = constants::knightSpriteHeight;
	m_spriteScale = constants::knightSpriteScale;
	m_sprite.setTexture(*m_texturesManager->loadAndGetTexture("playerIdle", "./assets/player/_Idle.png"));
	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::knightShapeWidth, constants::knightShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	// Initialize other attributes
	m_entityName = "player";
	initTexturesMap();
	m_speed = constants::playerSpeed;
	m_jumpHeight = constants::playerJumpHeight;
	m_hp = constants::playerHp;
}

void Player::update(float& deltaTime)
{
	// Checks if entity is dead
	updateDeath();

	if (!m_dying)
	{
		bool conditionRunLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);
		bool conditionRunRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right);
		bool conditionJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);

		updateMovement(conditionRunLeft, conditionRunRight, conditionJump, deltaTime);

		bool conditionAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z);

		updateAttack(conditionAttack);

		move(deltaTime);

		updateCooldownDamage();
	}

	// Add gravity when on dying state
	updateGravityWhenDying(deltaTime);

	updateLimits();
}
