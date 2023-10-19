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
	// Name of the current texture set in the entity
	std::string m_currentTexture{};

	// Amount of frame that the current texture has
	int m_currentAnimationFramesAmount{};

	// Counter to store the current frame of the sprite. Eg.: Running sprite has 5 frames (0-4) and it is now on 3rd frame, so m_frameCount == 2
	int m_frameCount{ 0 };

	// These maps helps to generalize the textures so it doesn't have to be coded inside each derived entity
	std::unordered_map<std::string, std::string> m_texturesActionName{};
	std::unordered_map<std::string, std::string> m_texturesNamePath{};

	// Useful to identify if the entity is player, enemy, etc...
	std::string m_entityName;
};
