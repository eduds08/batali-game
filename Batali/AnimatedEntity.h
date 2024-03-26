#pragma once

#include "DrawableEntity.h"

class AnimatedEntity : public DrawableEntity
{
public:
	AnimatedEntity();
	virtual ~AnimatedEntity() = default;

	// Called inside the animationThread. It's here where all animation happens.
	virtual void updateAnimation();

	// Called when the AnimatedEntity changes its sprite. Eg.: from running sprite to jumping sprite.
	void changeCurrentTexture(const std::string& textureName, const std::string& texturePath, bool loopAnimation);
	
	// Sets the next frame of the animation and when it hits the last frame, it starts from beginning again (if loop is true, otherwise it sets another texture like Idle).
	void animateSprite();

	// Called once for each entity in the initialization
	void initTexturesMap();

	const std::string& getEntityName() const { return m_entityName; }

	virtual void updateTexture() {}

protected:
	// Name of the current texture set in the entity
	std::string m_currentTexture{};

	// Amount of frames that the current texture has
	int m_currentAnimationFramesAmount{};

	// A counter to store the current frame of the sprite. Eg.: Running sprite has 5 frames (0-4) and it is now on 3rd frame, so m_frameCount == 2
	int m_frameCount{ 0 };

	// Action - Name. Eg.: Jumping - fire_knightJumping
	std::unordered_map<std::string, std::string> m_texturesActionName{};

	// Name - Path. Eg.: fire_knightJumping - ./assets/fire_knight/_Jumping.png
	std::unordered_map<std::string, std::string> m_texturesNamePath{};

	// Useful to identify the entity and its assets folder
	std::string m_entityName{};

	// If loopAnimation is false, the animation only plays once per execution (Eg.: roll, attack, hitted, die, etc...)
	bool m_loopAnimation{ false };

	// Useful for animation with loopAnimation = false. So it notifies that the animation has ended
	bool m_animationEnd{ false };
};
