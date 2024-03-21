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
	// Stamina and maybe rollSpeed. This state will be friend of character and stamina will be a character
	// attribute instead of WalkingEntity

	float m_rollSpeed{};
};
