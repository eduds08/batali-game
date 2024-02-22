#include "HealthBarUI.h"

HealthBarUI::HealthBarUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, const int* entityHp)
	: UI{ textureName, texturePath, position }
{
	m_spriteWidth = constants::healthBarSpriteWidth;
	m_spriteHeight = constants::healthBarSpriteHeight;

	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });

	if (entityHp != nullptr)
	{
		m_entityTotalHpFraction = static_cast<int>((*entityHp) / static_cast<float>(constants::healthBarFramesAmount - 1));
		m_entityHp = entityHp;
	}
	
	// The code below (from line 16 - 21) will be removed later:

	if (textureName == "enemyHealthBar")
	{
		m_sprite.setOrigin(sf::Vector2f{static_cast<float>(m_spriteWidth), m_sprite.getOrigin().y});
	}

	m_sprite.setScale(2.f, 2.f);
}

void HealthBarUI::update()
{
	for (int i = 0; i < constants::healthBarFramesAmount - 1; ++i)
	{
		if (*m_entityHp <= m_entityTotalHpFraction * i)
		{
			m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * (constants::healthBarFramesAmount - 1 - i), 0, m_spriteWidth, m_spriteHeight });
			break;
		}
	}
}

void HealthBarUI::setEntityHp(const int* entityHp)
{
	m_entityTotalHpFraction = static_cast<int>((*entityHp) / static_cast<float>(constants::healthBarFramesAmount - 1));
	m_entityHp = entityHp;
}
