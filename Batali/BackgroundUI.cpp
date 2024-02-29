#include "BackgroundUI.h"

BackgroundUI::BackgroundUI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i size, float scale)
	: UI{}
{
	setTexture(textureName, texturePath);

	m_spriteWidth = size.x;
	m_spriteHeight = size.y;

	setOrigin(sf::Vector2f{static_cast<float>(m_spriteWidth) / 2.f, static_cast<float>(m_spriteHeight) / 2.f});

	setScale(scale);

	setPosition(position);
}

void BackgroundUI::init(const std::string& textureName, const std::string& texturePath, sf::Vector2f position, sf::Vector2i size, float scale)
{
	setTexture(textureName, texturePath);

	m_spriteWidth = size.x;
	m_spriteHeight = size.y;

	setOrigin(sf::Vector2f{static_cast<float>(m_spriteWidth) / 2.f, static_cast<float>(m_spriteHeight) / 2.f});

	setScale(scale);

	setPosition(position);
}
