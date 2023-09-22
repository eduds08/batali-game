#include "Ground.h"

Ground::Ground(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, sf::Vector2f position)
	: DrawableEntity{ spriteWidth, spriteHeight, shapeWidth, shapeHeight }
{
	setSpriteTexture("ground", "./dirt.png");
	setShapeSettings(position);
	setSpriteSettings();
}
