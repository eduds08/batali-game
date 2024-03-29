#pragma once

class Player;

class IAnimatingComponent
{
public:
	virtual ~IAnimatingComponent() = default;

	virtual void initTextures(Player& player) = 0;

	virtual void update(Player& player) = 0;
};
