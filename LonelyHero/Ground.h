#pragma once

#include "DrawableEntity.h"

class Ground : public DrawableEntity
{
public:
	Ground(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, sf::Vector2f position);
	virtual ~Ground() = default;
};
