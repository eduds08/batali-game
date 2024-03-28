#pragma once

class Player;

class IColliderComponent
{
public:
	virtual ~IColliderComponent() = default;

	virtual void update(Player& player, float& deltaTime) = 0;
};
