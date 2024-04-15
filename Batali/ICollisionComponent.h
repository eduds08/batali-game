#pragma once

class GameObject;
class World;

class ICollisionComponent
{
public:
	virtual ~ICollisionComponent() = default;

	virtual void update(GameObject& gameObject, World& world) = 0;
};
