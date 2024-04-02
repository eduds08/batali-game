#pragma once

class GameObject;
class AttackHitbox;
class World;

class IAttackComponent
{
public:
	virtual ~IAttackComponent() = default;

	virtual void update(GameObject& gameObject, World& world, float& deltaTime) = 0;

	virtual const AttackHitbox* getAttackHitbox() const = 0;
};
