#pragma once

#include "DrawableEntity.h"

class Ground : public DrawableEntity
{
public:
	Ground(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, float positionX, float positionY);
	virtual ~Ground() = default;
};
