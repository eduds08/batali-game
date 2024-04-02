#pragma once

#include "IAttackComponent.h"
#include "AttackHitbox.h"

class PlayerAttackComponent : public IAttackComponent
{
public:
	PlayerAttackComponent();
	virtual ~PlayerAttackComponent();

	virtual void update(GameObject& gameObject, World& world, float& deltaTime);

	virtual const AttackHitbox* getAttackHitbox() const { return m_attackHitbox; }

private:
	AttackHitbox* m_attackHitbox{ nullptr };

};
