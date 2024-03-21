#pragma once

#include "CharacterState.h"

class JumpingState : public CharacterState
{
public:
	JumpingState() {}
	virtual ~JumpingState() = default;

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character);
};
