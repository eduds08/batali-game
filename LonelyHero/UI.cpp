#include "UI.h"

UI::UI(const std::string& textureName, const std::string& texturePath, sf::Vector2f position)
	: DrawableEntity{}
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));

	m_sprite.setPosition(position);
}
