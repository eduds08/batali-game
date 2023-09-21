#pragma once

#include <SFML/Graphics.hpp>

class AnimationManager
{
public:
	AnimationManager() {}
	~AnimationManager() {}

	static void animateSprite(sf::Sprite& sprite, int framesAmount, int width, int height, int& count);
};
