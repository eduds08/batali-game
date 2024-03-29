#pragma once

#include "AbstractAnimation.h"

class PlayedOnceAnimation : public AbstractAnimation
{
public:
	PlayedOnceAnimation(const std::string& name = "", const sf::Vector2i& frameSize = {0, 0}, sf::Texture* texture = nullptr);
	virtual ~PlayedOnceAnimation();

	virtual void update();

private:
	bool m_animationEnd{};
};
