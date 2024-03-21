#pragma once

#include "CharacterState.h"

class FallingState : public CharacterState
{
public:
	FallingState() {}
	virtual ~FallingState() = default;

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character);
};
