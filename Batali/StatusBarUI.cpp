#include "StatusBarUI.h"

StatusBarUI::StatusBarUI(const std::string& textureName, const std::string& texturePath, sf::Vector2i size)
	: UI{}
{
	init(textureName, texturePath, size);
}

void StatusBarUI::init(const std::string& textureName, const std::string& texturePath, sf::Vector2i size)
{
	setTexture(textureName, texturePath);

	m_spriteWidth = size.x;
	m_spriteHeight = size.y;

	m_sprite.setTextureRect(sf::IntRect{ 0, 0, m_spriteWidth, m_spriteHeight });
}

void StatusBarUI::update()
{
	for (int i = 0; i <= static_cast<int>(m_sprite.getTexture()->getSize().x / m_spriteWidth) - 1; ++i)
	{
		if (*m_actorStatus <= m_actorTotalStatusFraction * i)
		{
			m_sprite.setTextureRect(sf::IntRect{ m_spriteWidth * (static_cast<int>(m_sprite.getTexture()->getSize().x / m_spriteWidth) - 1 - i), 0, m_spriteWidth, m_spriteHeight });
			break;
		}
	}
}

void StatusBarUI::setActorStatus(const int* actorStatus)
{
	m_actorTotalStatusFraction = static_cast<int>((*actorStatus) / static_cast<float>(static_cast<int>(m_sprite.getTexture()->getSize().x / m_spriteWidth) - 1));
	m_actorStatus = actorStatus;
}
