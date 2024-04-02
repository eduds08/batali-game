#pragma once

#include "IPhysicsComponent.h"

class PlayerPhysicsComponent : public IPhysicsComponent
{
public:
	PlayerPhysicsComponent();
	virtual ~PlayerPhysicsComponent();

	virtual void update(GameObject& gameObject, float& deltaTime);

	virtual void move(GameObject& gameObject, float& deltaTime);
};
