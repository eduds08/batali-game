#include "Ground.h"

Ground::Ground(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, float positionX, float positionY)
	: DrawableEntity{ spriteWidth, spriteHeight, shapeWidth, shapeHeight }
{
	setSpriteTexture("ground", "./dirt.png");
	setShapeSettings(positionX, positionY);
	setSpriteSettings();
}
