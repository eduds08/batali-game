#pragma once

#include "CharacterState.h"

class RollingState : public CharacterState
{
public:
	RollingState() {}
	virtual ~RollingState() = default;

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character);
};
