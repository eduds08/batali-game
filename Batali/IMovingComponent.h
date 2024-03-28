#pragma once

class Player;

class IMovingComponent
{
public:
	virtual ~IMovingComponent() = default;

	virtual void update(Player& player, float& deltaTime) = 0;
};
