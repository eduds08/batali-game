#pragma once

#include "IPhysicsComponent.h"

class PlayerPhysicsComponent : public IPhysicsComponent
{
public:
	PlayerPhysicsComponent() = default;
	virtual ~PlayerPhysicsComponent() = default;

	virtual void update(GameObject& gameObject, float& deltaTime);

	virtual void move(GameObject& gameObject, float& deltaTime);
};
