#pragma once

#include <string>
class Player;
class AttackHitbox;
class World;

class IChosenCharacterState
{
public:
	virtual ~IChosenCharacterState() = default;

	virtual void update(Player& player, World& world, float& deltaTime) = 0;

	virtual void enter(Player& player) = 0;

	virtual const std::string& getChosenCharacterName() const = 0;

	virtual void updateAttackHitbox(Player& player, AttackHitbox& attackHitbox) = 0;

	virtual bool checkIfIsAttacking(Player& player, Player& enemy, const AttackHitbox& attackHitbox) = 0;

	virtual const AttackHitbox& getAttackHitbox() const = 0;

	virtual void attack(Player& player, Player& enemy) = 0;

	virtual void knockbackMove(Player& player, float& deltaTime) = 0;
};
