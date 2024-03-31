#pragma once

class Player;
class AttackHitbox;

class IAttackingComponent
{
public:
	virtual ~IAttackingComponent() = default;

	virtual void update(Player& player, float& deltaTime) = 0;

	virtual const AttackHitbox* getAttackHitbox() const = 0;
};
