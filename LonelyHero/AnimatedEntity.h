#pragma once

#include "DrawableEntity.h"
#include "AnimationManager.h"

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity(int spriteWidth, int spriteHeight, int animationFramesAmount, float animationSwitchTime);
	virtual ~AnimatedEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void updateAnimation(float& deltaTime);

protected:
	std::string m_currentTexture{};

	int m_currentAnimationFramesAmount{};
	float m_animationSwitchTime{};

	int m_frameCount{};
	float m_animationTotalTime{};
};
