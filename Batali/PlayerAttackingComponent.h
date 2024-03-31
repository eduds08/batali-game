#pragma once

#include "IAttackingComponent.h"
#include "AttackHitbox.h"

class PlayerAttackingComponent : public IAttackingComponent
{
public:
	PlayerAttackingComponent();
	virtual ~PlayerAttackingComponent();

	virtual void update(Player& player, float& deltaTime);

	virtual const AttackHitbox* getAttackHitbox() const { return m_attackHitbox; }

private:
	AttackHitbox* m_attackHitbox{ nullptr };

};
