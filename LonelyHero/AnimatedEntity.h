#pragma once

#include "DrawableEntity.h"

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity();
	virtual ~AnimatedEntity() = default;

	void updateAnimation();

	void changeCurrentTexture(int animationFramesAmount, const std::string& textureName, const std::string& texturePath);
	void animateSprite();

	void initTexturesMap();

	// pure virtual method, defined in derived classes
	virtual void updateTexture() = 0;
protected:
	// textureName for the current texture applied to the object
	std::string m_currentTexture{};

	int m_currentAnimationFramesAmount{};

	// Counter to store the current frame of the animation. Eg.: walking animation has 5 frames (0-4) and it is now on 3rd frame, so m_frameCount == 2
	int m_frameCount{ 0 };

	std::unordered_map<std::string, std::string> m_texturesActionName{};
	std::unordered_map<std::string, std::string> m_texturesNamePath{};

	std::string m_entityName;
	
};
