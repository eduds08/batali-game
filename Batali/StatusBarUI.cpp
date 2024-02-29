#include "StatusBarUI.h"

StatusBarUI::StatusBarUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i size)
	: UI{textureName, texturePath, position}
{
	m_spriteWidth = size.x;
	m_spriteHeight = size.y;

	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });
}

void StatusBarUI::update()
{
	for (int i = 0; i < static_cast<int>(m_sprite.getTexture()->getSize().x / m_spriteWidth) - 1; ++i)
	{
		if (*m_entityStatus <= m_entityTotalStatusFraction * i)
		{
			m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * (static_cast<int>(m_sprite.getTexture()->getSize().x / m_spriteWidth) - 1 - i), 0, m_spriteWidth, m_spriteHeight });
			break;
		}
	}
}

void StatusBarUI::setEntityStatus(const int* entityStatus)
{
	m_entityTotalStatusFraction = static_cast<int>((*entityStatus) / static_cast<float>(static_cast<int>(m_sprite.getTexture()->getSize().x / m_spriteWidth) - 1));
	m_entityStatus = entityStatus;
}
