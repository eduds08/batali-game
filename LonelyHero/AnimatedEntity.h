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

	virtual void updateTexture() = 0;
	void updateTextureAndAnimation();
	void changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath);

protected:
	std::string m_currentTexture{};

	int m_currentAnimationFramesAmount{};

	int m_frameCount{ 0 };

	bool m_isRunning{ false };
	bool m_isAttacking{ false };

	int m_facingRight{ 1 };
	std::string m_previousAttackingAnimation{};
};
