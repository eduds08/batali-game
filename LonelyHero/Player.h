#pragma once

#include "SwordEntity.h"
#include "Constants.h"

class Player : public SwordEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~Player() = default;

	void update(float& deltaTime);
private:
	
};
