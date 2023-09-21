#pragma once

#include "DrawableEntity.h"

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity(int frameWidth, int frameHeight, int frameAmount, float switchAnimationTime);
	virtual ~AnimatedEntity() = default;

	virtual void setSpriteTexture(const std::string& textureName, const std::string& texturePath);

	void updateAnimation(float& deltaTime);

protected:
	std::string m_currentSprite{};

	int m_frameAmount{};
	float m_switchAnimationTime{};

	int m_frameCount{ 0 };
	float m_totalAnimationTime{ 0 };
};
