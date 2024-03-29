#pragma once

#include "IAnimatingComponent.h"

#include "TexturesManager.h"
#include "AbstractAnimation.h"

const std::string IDLE_ANIMATION{ "_Idle" };
const std::string ROLL_ANIMATION{ "_Roll" };

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

	std::vector<std::string> m_playerAnimationNames{ IDLE_ANIMATION, "_Running", "_Jumping", "_Falling", ROLL_ANIMATION, "_Attack1", "_Attack2", "_AirAttack", "_Hitted", "_FastHitted", "_Dying", "_Ultimate"};
};
