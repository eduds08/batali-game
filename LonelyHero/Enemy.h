#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class Enemy : public AnimatedEntity, public ColliderEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, float spriteScale, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	void updateTexture();

	void updateTextureAndAnimation();

	void changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath);
private:
	int m_facingRight{ 1 };
};
