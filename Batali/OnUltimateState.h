#pragma once

#include "CharacterState.h"

class OnUltimateState : public CharacterState
{
public:
	OnUltimateState() {}
	virtual ~OnUltimateState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);
};
