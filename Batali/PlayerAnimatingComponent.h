#pragma once

#include "IAnimatingComponent.h"

#include "TexturesManager.h"
#include "AbstractAnimation.h"

#include "Constants.h"

using namespace constants;

class PlayerAnimatingComponent : public IAnimatingComponent
{
public:
	PlayerAnimatingComponent();
	virtual ~PlayerAnimatingComponent();

	void initTextures(Player& player);

	virtual void update(Player& player);

private:
	TexturesManager& m_texturesManager{ TexturesManager::getInstance() };

	AbstractAnimation* m_currentAnimation{ nullptr };

	std::vector<std::string> m_playerAnimationNames{ IDLE_ANIMATION, RUNNING_ANIMATION, JUMPING_ANIMATION, FALLING_ANIMATION, ROLL_ANIMATION, ATTACK_1_ANIMATION, ATTACK_2_ANIMATION, AIR_ATTACK_ANIMATION,
		HITTED_ANIMATION, FAST_HITTED_ANIMATION, DYING_ANIMATION, ULTIMATE_ANIMATION };
};
