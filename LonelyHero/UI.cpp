#include "UI.h"

UI::UI(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
	: DrawableEntity{}
{
	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));

	m_sprite.setPosition(position);
}
