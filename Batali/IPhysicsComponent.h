#pragma once

class Player;
class World;

class IPhysicsComponent
{
public:
	virtual ~IPhysicsComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime) = 0;
};
