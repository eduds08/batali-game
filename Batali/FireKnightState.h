#pragma once

#include "AttackHitbox.h"
#include "IChosenCharacterState.h"

class World;
class Player;

#include "Constants.h"

using namespace constants;

class FireKnightState : public IChosenCharacterState
{
public:
	FireKnightState();
	virtual ~FireKnightState();

	virtual void update(Player& player, World& world, float& deltaTime);

	virtual void enter(Player& player);

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player, AttackHitbox& attackHitbox);

	virtual bool checkIfIsAttacking(Player& player, Player& enemy, const AttackHitbox& attackHitbox);

	virtual const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	virtual void attack(Player& player, Player& enemy);

	virtual void knockbackMove(Player& player, float& deltaTime);

private:
	std::string m_name{ "fire_knight" };

	AttackHitbox m_attackHitbox{};
};
