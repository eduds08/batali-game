#include "HealthBarUI.h"

#include <iostream>

HealthBarUI::HealthBarUI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
	: UI{position, textureName, texturePath}
{
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });

	m_sprite.setScale(2.f, 2.f);
}

void HealthBarUI::updateHealthBar()
{
	if (*m_entityHp <= 0) {
		m_sprite.setTextureRect(sf::IntRect{ 240, 0, m_spriteWidth, m_spriteHeight });
	}
	else if (*m_entityHp < (m_entityTotalHp / 5.f) * 1) {
		m_sprite.setTextureRect(sf::IntRect{ 192, 0, m_spriteWidth, m_spriteHeight });
	}
	else if (*m_entityHp < (m_entityTotalHp / 5.f) * 2) {
		m_sprite.setTextureRect(sf::IntRect{ 144, 0, m_spriteWidth, m_spriteHeight });
	}
	else if (*m_entityHp < (m_entityTotalHp / 5.f) * 3) {
		m_sprite.setTextureRect(sf::IntRect{ 96, 0, m_spriteWidth, m_spriteHeight });
	}
	else if (*m_entityHp < (m_entityTotalHp / 5.f) * 4) {
		m_sprite.setTextureRect(sf::IntRect{ 48, 0, m_spriteWidth, m_spriteHeight });
	}
}

void HealthBarUI::setEntityHp(const int* entityHp)
{
	m_entityTotalHp = *entityHp;
	m_entityHp = entityHp;
}
