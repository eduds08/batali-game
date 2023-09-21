#pragma once

#include "DrawableEntity.h"

class Ground : public DrawableEntity
{
public:
	Ground(int frameWidth, int frameHeight, float xCoord, float yCoord);
	virtual ~Ground() = default;
	
private:

};
