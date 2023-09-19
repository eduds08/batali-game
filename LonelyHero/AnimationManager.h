#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <map>
#include <string>

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	static void animateSprite(sf::Sprite& sprite, int framesAmount, int width, int height, int& count);

private:
};

