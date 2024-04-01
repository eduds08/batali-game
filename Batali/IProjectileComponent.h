#pragma once

class Player;
class World;

class IProjectileComponent
{
public:
	virtual ~IProjectileComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime) = 0;
};
