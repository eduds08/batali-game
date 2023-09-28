#pragma once

#include "DrawableEntity.h"
#include "AnimationManager.h"
#include <thread>

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity(int spriteWidth, int spriteHeight, float spriteScale, int animationFramesAmount);
	virtual ~AnimatedEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void updateAnimation();

protected:
	std::string m_currentTexture{};

	int m_currentAnimationFramesAmount{};

	int m_frameCount{ 0 };
};
