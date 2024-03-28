#pragma once

class Player;

class IAnimatingComponent
{
public:
	virtual ~IAnimatingComponent() = default;

	virtual void update(Player& player) = 0;
};
