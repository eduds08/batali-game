#pragma once

#include "AttackEntity.h"
#include "Constants.h"

class Player : public AttackEntity
{
public:
	Player(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~Player() = default;

	void update(float& deltaTime);

	void updateAttack();

	// inherited from AnimatedEntity class
	virtual void updateTexture();

	

private:
	
};
