#pragma once

#include "ColliderEntity.h"

class CharacterState;

class Character : public ColliderEntity
{
public:
	Character();
	virtual ~Character() {}

	void handleCondition(const std::string& condition);

	void update(float& deltaTime);

	CharacterState* m_state{ };

	virtual void updateAttackHitbox() = 0;

	friend class RollingState;
	friend class RunningState;
	friend class JumpingState;
	friend class FallingState;
	friend class IdleState;
	friend class AttackingState;
	friend class OnUltimateState;

protected:
	int m_hp{ 1300 };
};
