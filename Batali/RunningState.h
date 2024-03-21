#pragma once

#include "CharacterState.h"

class RunningState : public CharacterState
{
public:
	RunningState();
	virtual ~RunningState() = default;

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character);

private:
};
