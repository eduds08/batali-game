#pragma once

#include "IAnimationComponent.h"

#include "TexturesManager.h"
#include "AbstractAnimation.h"

#include "Constants.h"

using namespace constants;

class PlayerAnimationComponent : public IAnimationComponent
{
public:
	PlayerAnimationComponent() = default;
	virtual ~PlayerAnimationComponent() = default;

	virtual void initTextures(GameObject& gameObject);

	virtual void setNewAnimation(GameObject& gameObject, const std::string& name, bool isLooping);

	virtual std::unique_ptr<AbstractAnimation>& getCurrentAnimation() { return m_currentAnimation; }

	virtual void update(GameObject& gameObject);

private:
	TexturesManager& m_texturesManager{ TexturesManager::getInstance() };

	std::unique_ptr<AbstractAnimation> m_currentAnimation{ nullptr };

	std::vector<std::string> m_playerAnimationNames{ IDLE_ANIMATION, RUNNING_ANIMATION, JUMPING_ANIMATION, FALLING_ANIMATION, ROLL_ANIMATION, ATTACK_1_ANIMATION, ATTACK_2_ANIMATION, AIR_ATTACK_ANIMATION,
		HITTED_ANIMATION, FAST_HITTED_ANIMATION, DYING_ANIMATION, ULTIMATE_ANIMATION };
};
