#include "Player.h"

Player::Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: SwordEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, entityName, shapeWidth, shapeHeight, firstPosition }
{
}

void Player::update(float& deltaTime)
{
	// Only sets dead = true when the dead animation ends, that way we can still call updateAnimation() even if hp <= 0
	if (m_dying && m_frameCount >= 9)
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
}