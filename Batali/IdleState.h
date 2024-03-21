#pragma once

#include "CharacterState.h"

class IdleState : public CharacterState
{
public:
	IdleState() {}
	virtual ~IdleState() = default;

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character);
};
