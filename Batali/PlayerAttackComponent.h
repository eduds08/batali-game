#pragma once

#include "IAttackComponent.h"
#include "AttackHitbox.h"

class World;

class PlayerAttackComponent : public IAttackComponent
{
public:
	PlayerAttackComponent();
	virtual ~PlayerAttackComponent();

	virtual void update(GameObject& gameObject, World& world, float& deltaTime);

	virtual const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	// Moves the actor after being hit. attackDirection -> direction of the attack (from left or right)
	void knockbackMove(GameObject& gameObject, float& deltaTime);

private:
	AttackHitbox m_attackHitbox{};

};
