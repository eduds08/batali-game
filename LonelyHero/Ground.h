#pragma once

#include "DrawableEntity.h"

class Ground : public DrawableEntity
{
public:
	Ground(int spriteWidth, int spriteHeight, sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~Ground() = default;
};
