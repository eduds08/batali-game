#pragma once

#include "IPhysicsComponent.h"

class ProjectilePhysicsComponent : public IPhysicsComponent
{
public:
	ProjectilePhysicsComponent() = default;
	virtual ~ProjectilePhysicsComponent() = default;

	virtual void update(GameObject& gameObject, float& deltaTime);

	virtual void move(GameObject& gameObject, float& deltaTime);
};
