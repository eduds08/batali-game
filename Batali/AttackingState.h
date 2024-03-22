#pragma once

#include "CharacterState.h"

class AttackingState : public CharacterState
{
public:
	AttackingState() {}
	virtual ~AttackingState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);
};
