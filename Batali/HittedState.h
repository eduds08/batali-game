#pragma once

#include "CharacterState.h"

class HittedState : public CharacterState
{
public:
	HittedState(const std::string& hittedMode, Character* attacker = nullptr);
	virtual ~HittedState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);

private:
	std::string m_hittedMode{};

	Character* m_attacker{ nullptr };
};
