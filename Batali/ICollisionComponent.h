#pragma once

class Player;
class World;

class ICollisionComponent
{
public:
	virtual ~ICollisionComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime) = 0;
};
