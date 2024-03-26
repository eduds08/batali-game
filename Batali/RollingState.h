#pragma once

#include "CharacterState.h"

class RollingState : public CharacterState
{
public:
	RollingState() {}
	virtual ~RollingState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);

private:
	float m_rollSpeed{ 220.f };
};
