#include "Ground.h"

Ground::Ground(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime, float xCoord, float yCoord)
	: DrawableEntity{frameWidth, frameHeight, frameAmount, switchAnimationTime}
{
	setSpriteTexture("ground", "./dirt.png");
	setSpriteSettings(xCoord, yCoord);

	m_sprite.setOrigin(0.f, 0.f);
}

Ground::~Ground()
{
}
