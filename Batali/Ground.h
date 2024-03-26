#pragma once

#include "SpriteActor.h"
#include "Constants.h"

class Ground : public SpriteActor
{
public:
	Ground(sf::Vector2f position, const std::string& textureName, const std::string& texturePath);
	virtual ~Ground() = default;
};
