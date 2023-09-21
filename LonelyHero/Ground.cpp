#include "Ground.h"

Ground::Ground(int frameWidth, int frameHeight, float xCoord, float yCoord)
	: DrawableEntity{frameWidth, frameHeight}
{
	setSpriteTexture("ground", "./dirt.png");
	setSpriteSettings(xCoord, yCoord);

	m_sprite.setOrigin(0.f, 0.f);
}

Ground::~Ground()
{
}
