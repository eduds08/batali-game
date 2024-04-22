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
	FireKnightState() = default;
	virtual ~FireKnightState() = default;

	virtual void update(Player& player, World& world, float& deltaTime);

	virtual void enter(Player& player);

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player);

	virtual bool checkIfIsAttacking(Player& player, const AttackHitbox& attackHitbox);

	virtual const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	virtual void attack(Player& player, Player& enemy);

	virtual void knockbackMove(Player& player, float& deltaTime);

private:
	std::string m_name{ "fire_knight" };

	AttackHitbox m_attackHitbox{};
};
