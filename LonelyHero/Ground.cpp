#include "Ground.h"

Ground::Ground(int spriteWidth, int spriteHeight, sf::Vector2f position, const std::string& textureName, const std::string& texturePath)
	: DrawableEntity{ spriteWidth, spriteHeight }
{
	setSpriteTexture(textureName, texturePath);
	m_sprite.setPosition(position);
}
