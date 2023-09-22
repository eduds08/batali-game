#pragma once

#include "DrawableEntity.h"
#include "AnimationManager.h"

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity(int spriteWidth, int spriteHeight, float shapeWidth, float shapeHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~AnimatedEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void updateAnimation(float& deltaTime);

protected:
	std::string m_currentSprite{};

	int m_animationFramesAmount{};
	float m_animationSwitchTime{};

	int m_frameCount{};
	float m_animationTotalTime{};
};
