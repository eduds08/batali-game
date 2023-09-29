#include "AttackEntity.h"

AttackEntity::AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: MovableEntity{ spriteWidth, spriteHeight, spriteScale, textureName, texturePath, animationFramesAmount, shapeWidth, shapeHeight, firstPosition }
{
}

void AttackEntity::updateAttack(const std::string& entity)
{
	if (m_isAttacking)
	{
		m_velocity.x = 0.f;
	}

	if ((m_currentTexture == entity + "Attacking2" && m_frameCount >= 5) || (m_currentTexture == entity + "Attacking1" && m_frameCount >= 3))
	{
		m_previousAttackingAnimation = m_currentTexture;
		m_isAttacking = false;
	}
}

void AttackEntity::updateHitbox()
{
	if (m_isAttacking)
	{
		if (!m_hitbox)
		{
			m_hitbox = { new sf::RectangleShape{sf::Vector2f{constants::swordHitboxWidth, constants::swordHitboxHeight}} };
			m_hitbox->setOrigin(m_hitbox->getSize() / 2.f);
			m_hitbox->setOutlineColor(sf::Color::Red);
			m_hitbox->setOutlineThickness(1.f);
		}
	}
	else
	{
		if (m_hitbox)
		{
			delete m_hitbox;
			m_hitbox = nullptr;
		}
	}

	if (m_hitbox)
	{
		m_hitbox->setPosition(getPosition() + sf::Vector2f((20.f + getSize().x) * m_facingRight, 0.f));
	}
}

sf::RectangleShape* AttackEntity::getHitbox()
{
	return m_hitbox ? m_hitbox : nullptr;
}
