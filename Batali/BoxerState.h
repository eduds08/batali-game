#pragma once

#include "IChosenCharacterState.h"

#include "AttackHitbox.h"
#include "Constants.h"
using namespace constants;

class BoxerState : public IChosenCharacterState
{
public:
	BoxerState() = default;
	virtual ~BoxerState() = default;

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player, AttackHitbox* attackHitbox);

private:
	std::string m_name{ "boxer" };
};
