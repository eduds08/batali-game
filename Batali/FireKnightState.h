#pragma once

#include "AttackHitbox.h"
#include "IChosenCharacterState.h"

#include "Constants.h"

using namespace constants;

class FireKnightState : public IChosenCharacterState
{
public:
	FireKnightState();
	virtual ~FireKnightState();

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player, AttackHitbox* attackHitbox);

	virtual void checkIfIsAttacking(Player& enemy, AttackHitbox* attackHitbox);

private:
	std::string m_name{ "fire_knight" };
};
