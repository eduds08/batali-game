#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::animateSprite(sf::Sprite& sprite, int framesAmount, int width, int height, int& count)
{
	if (count == framesAmount)
		count = 0;
	sprite.setTextureRect(sf::IntRect{ width * count, 0, width, height });
	++count;
}
