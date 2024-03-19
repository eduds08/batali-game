#include "ImageButtonUI.h"

ImageButtonUI::ImageButtonUI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
	: ButtonUI{}
{
	init(position, textureName, texturePath);
}

void ImageButtonUI::init(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
{
	setTexture(textureName, texturePath);

	m_spriteWidth = CHARACTER_PORTRAIT_WIDTH;
	m_spriteHeight = CHARACTER_PORTRAIT_HEIGHT;

	setSpritePosition(position);

	m_buttonBorder = sf::RectangleShape{ sf::Vector2f{static_cast<float>(m_spriteWidth), static_cast<float>(m_spriteHeight)} };

	m_buttonBorder.setOutlineThickness(1.f);

	m_buttonBorder.setPosition(getSpritePosition());
	m_buttonBorder.setFillColor(sf::Color::Transparent);
}

void ImageButtonUI::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
	window.draw(m_buttonBorder);
}

void ImageButtonUI::update(bool onHover)
{
	if (onHover)
	{
		m_buttonBorder.setOutlineColor(sf::Color::Red);
	}
	else
	{
		m_buttonBorder.setOutlineColor(sf::Color::White);
	}
}
