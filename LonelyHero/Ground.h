#pragma once

#include "DrawableEntity.h"

class Ground : public DrawableEntity
{
public:
	Ground(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime, float xCoord, float yCoord);
	~Ground();
	
private:

};
