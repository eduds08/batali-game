#pragma once

class Player;

class IPhysicsComponent
{
public:
	virtual ~IPhysicsComponent() = default;

	virtual void update(Player& player, float& deltaTime) = 0;
};
