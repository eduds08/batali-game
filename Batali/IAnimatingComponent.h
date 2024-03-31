#pragma once

#include <string>

class AbstractAnimation;
class Player;

class IAnimatingComponent
{
public:
	virtual ~IAnimatingComponent() = default;

	virtual void initTextures(Player& player) = 0;

	virtual void setNewAnimation(Player& player, const std::string& name, bool isLooping) = 0;

	virtual AbstractAnimation* getCurrentAnimation() = 0;

	virtual void update(Player& player) = 0;
};
