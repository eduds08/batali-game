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

	friend class RollingState;
	friend class RunningState;
	friend class JumpingState;
	friend class FallingState;
	friend class IdleState;

protected:
	int m_hp{ 1300 };

	float m_jumpHeight{ 85.f };
};
