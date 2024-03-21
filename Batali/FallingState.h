#pragma once

#include "CharacterState.h"

class FallingState : public CharacterState
{
public:
	FallingState() {}
	virtual ~FallingState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);
};
