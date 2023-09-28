#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class Enemy : public AnimatedEntity, public ColliderEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	void updateTexture();

	void updateTextureAndAnimation();

	void changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath);
private:
	int m_facingRight{ 1 };
};
