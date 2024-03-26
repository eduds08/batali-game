#pragma once

#include "CharacterState.h"

class JumpingState : public CharacterState
{
public:
	JumpingState();
	virtual ~JumpingState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);

private:
	float m_jumpHeight{ 85.f };

	bool m_onFall{ false };
};
