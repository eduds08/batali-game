#include "AttackEntity.h"

AttackEntity::AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: MovableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
	m_hitbox = { sf::RectangleShape{sf::Vector2f{0.f, 0.f}} };
	m_hitbox.setOrigin(sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight } / 2.f);
	m_hitbox.setOutlineColor(sf::Color::Red);
	m_hitbox.setOutlineThickness(1.f);
}

void AttackEntity::updateAttack(const std::string& entity)
{
	if (m_isAttacking)
	{
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}

	if ((m_currentTexture == entity + "Attacking2" && m_frameCount >= 5) || (m_currentTexture == entity + "Attacking1" && m_frameCount >= 3))
	{
		m_previousAttackingAnimation = m_currentTexture;
		m_isAttacking = false;
	}
}

void AttackEntity::updateHitbox()
{
	if ((m_currentTexture == "playerAttacking1" && m_frameCount > 1) || (m_currentTexture == "playerAttacking2" && m_frameCount > 2))
	{
		if (m_hitbox.getSize() == sf::Vector2f{0.f, 0.f})
		{
			m_hitbox.setSize(sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight });
			m_hitbox.setPosition(getPosition() + sf::Vector2f((20.f + getSize().x) * m_facingRight, 0.f));
		}
	}
	else
	{
		if (m_hitbox.getSize() == sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight })
		{
			m_hitbox.setSize(sf::Vector2f{ 0.f, 0.f });
			m_hitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
		}
	}

	if (m_hitbox.getSize() == sf::Vector2f{ constants::swordHitboxWidth, constants::swordHitboxHeight })
	{
		m_hitbox.setPosition(getPosition() + sf::Vector2f((20.f + getSize().x) * m_facingRight, 0.f));
	}
}

