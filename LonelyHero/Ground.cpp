#include "Ground.h"

Ground::Ground(int spriteWidth, int spriteHeight, sf::Vector2f position)
	: DrawableEntity{ spriteWidth, spriteHeight }
{
	setSpriteTexture("ground", "./dirt.png");
	setSpriteSettings(position);
}
