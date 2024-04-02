#pragma once

class GameObject;

class IPhysicsComponent
{
public:
	virtual ~IPhysicsComponent() = default;

	virtual void update(GameObject& gameObject, float& deltaTime) = 0;

	virtual void move(GameObject& gameObject, float& deltaTime) = 0;
};
