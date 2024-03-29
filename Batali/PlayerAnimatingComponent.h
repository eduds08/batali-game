#pragma once

#include "IAnimatingComponent.h"

#include "TexturesManager.h"
#include "AbstractAnimation.h"

const std::string IDLE_ANIMATION{ "_Idle" };
const std::string ROLL_ANIMATION{ "_Roll" };
const std::string RUNNING_ANIMATION{ "_Running" };
const std::string JUMPING_ANIMATION{ "_Jumping" };
const std::string FALLING_ANIMATION{ "_Falling" };
const std::string ATTACK_1_ANIMATION{ "_Attack1" };
const std::string ATTACK_2_ANIMATION{ "_Attack2" };
const std::string AIR_ATTACK_ANIMATION{ "_AirAttack" };
const std::string ULTIMATE_ANIMATION{ "_Ultimate" };
const std::string HITTED_ANIMATION{ "_Hitted" };
const std::string FAST_HITTED_ANIMATION{ "_FastHitted" };
const std::string DYING_ANIMATION{ "_Dying" };

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
