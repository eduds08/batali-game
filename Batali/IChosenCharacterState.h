#pragma once

class Player;

class IChosenCharacterState
{
public:
	virtual ~IChosenCharacterState() = default;

	virtual void updateAttackHitbox(Player& player, AttackHitbox* attackHitbox) = 0;
};
