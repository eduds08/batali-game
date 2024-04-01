#pragma once

#include "IChosenCharacterState.h"

#include "AttackHitbox.h"
#include "Constants.h"
using namespace constants;

class WindHashashinState : public IChosenCharacterState
{
public:
	WindHashashinState() = default;
	virtual ~WindHashashinState() = default;

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player, AttackHitbox* attackHitbox);

	virtual void checkIfIsAttacking(Player& enemy, AttackHitbox* attackHitbox);

private:
	std::string m_name{ "wind_hashashin" };

	bool m_activateUltimate{ false };
};
