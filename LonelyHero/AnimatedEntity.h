#pragma once

#include "DrawableEntity.h"

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount);
	virtual ~AnimatedEntity() = default;

	void updateAnimation();

	void changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath);
	void animateSprite();

	virtual void updateTexture() = 0;
protected:
	std::string m_currentTexture{};

	int m_currentAnimationFramesAmount{};
	int m_frameCount{ 0 };
};
