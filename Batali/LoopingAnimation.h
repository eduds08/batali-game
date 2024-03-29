#pragma once

#include "AbstractAnimation.h"

class LoopingAnimation : public AbstractAnimation
{
public:
	LoopingAnimation(const std::string& name = "", const sf::Vector2i& frameSize = { 0, 0 }, sf::Texture* texture = nullptr);
	virtual ~LoopingAnimation();

	virtual void update();
};
