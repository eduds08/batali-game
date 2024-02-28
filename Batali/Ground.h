#pragma once

#include "DrawableEntity.h"
#include "Constants.h"

class Ground : public DrawableEntity
{
public:
	Ground(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~Ground() = default;
};
