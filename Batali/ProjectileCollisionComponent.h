#pragma once

#include "ICollisionComponent.h"

class ProjectileCollisionComponent : public ICollisionComponent
{
public:
	ProjectileCollisionComponent() = default;
	virtual ~ProjectileCollisionComponent() = default;

	virtual void update(GameObject& gameObject, World& world, float& deltaTime);
};
