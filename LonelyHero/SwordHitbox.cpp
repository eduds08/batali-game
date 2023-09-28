#include "SwordHitbox.h"

SwordHitbox::SwordHitbox(float shapeWidth, float shapeHeight, sf::Vector2f firstPosition)
	: ColliderEntity{shapeWidth, shapeHeight, firstPosition}
{
}

SwordHitbox::~SwordHitbox()
{
}
