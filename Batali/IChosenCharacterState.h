#pragma once

#include <string>
class Player;
class AttackHitbox;

class IChosenCharacterState
{
public:
	virtual ~IChosenCharacterState() = default;

	virtual const std::string& getChosenCharacterName() const = 0;

	virtual void updateAttackHitbox(Player& player, AttackHitbox* attackHitbox) = 0;

	virtual void checkIfIsAttacking(Player& enemy, AttackHitbox* attackHitbox) = 0;
};
