#pragma once

#include "CharacterState.h"

class DeadState : public CharacterState
{
public:
	DeadState() {}
	virtual ~DeadState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);
};
