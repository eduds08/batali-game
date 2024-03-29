#pragma once

#include "IPhysicsComponent.h"

class PlayerPhysicsComponent : public IPhysicsComponent
{
public:
	PlayerPhysicsComponent();
	virtual ~PlayerPhysicsComponent();

	virtual void update(Player& player, float& deltaTime);

	void move(Player& player, float& deltaTime);

private:

};
