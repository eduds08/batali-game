#pragma once

#include "IAnimatingComponent.h"

#include "TexturesManager.h"
#include "AbstractAnimation.h"

class PlayerAnimatingComponent : public IAnimatingComponent
{
public:
	PlayerAnimatingComponent();
	virtual ~PlayerAnimatingComponent();

	virtual void update(Player& player);

private:
	TexturesManager& m_texturesManager{ TexturesManager::getInstance() };

	AbstractAnimation* m_currentAnimation{ nullptr };

};
