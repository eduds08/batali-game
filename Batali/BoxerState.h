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

	virtual void enter(Player& player);

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player, AttackHitbox& attackHitbox);

	virtual void checkIfIsAttacking(Player& enemy, AttackHitbox& attackHitbox);

private:
	std::string m_name{ "boxer" };
};
