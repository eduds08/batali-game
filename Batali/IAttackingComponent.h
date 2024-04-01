#pragma once

class Player;
class AttackHitbox;
class World;

class IAttackingComponent
{
public:
	virtual ~IAttackingComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime) = 0;

	virtual const AttackHitbox* getAttackHitbox() const = 0;
};
