#include "Player.h"

Player::Player(sf::Vector2f firstPosition)
	: SwordEntity{ firstPosition }
{
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

	m_entityName = "player";
	initTexturesMap();

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ constants::knightShapeWidth, constants::knightShapeHeight});
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(firstPosition.x, firstPosition.y);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	m_speed = constants::playerSpeed;
	m_hp = 10000;
}

void Player::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_dying && m_frameCount >= m_currentAnimationFramesAmount - 1 && !m_dead)
	{
		die();
	}

	if (!m_dying)
	{
		updateMovement(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right), sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up), deltaTime);
		updateAttack(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z));

		move(deltaTime);

		updateCooldownDamage();
	}

	if (m_dying && !m_dead)
	{
		m_velocity.x = 0.f;
		m_velocity.y += constants::gravity * deltaTime;
		move(deltaTime);
	}
}