#include "Ground.h"

Ground::Ground(sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
	: DrawableEntity{}
{
	m_spriteWidth = TILE_SIZE_INT;
	m_spriteHeight = TILE_SIZE_INT;

	m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));

	m_sprite.setOrigin(sf::Vector2f{ m_spriteWidth / 2.f, m_spriteHeight / 2.f });
	m_sprite.setPosition(position);
}