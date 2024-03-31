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

	virtual void updateAttackHitbox(Player& player, AttackHitbox* attackHitbox);
};
