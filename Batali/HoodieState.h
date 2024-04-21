#pragma once

#include "IChosenCharacterState.h"

#include "AttackHitbox.h"
#include "Constants.h"
using namespace constants;

class HoodieState : public IChosenCharacterState
{
public:
	HoodieState() = default;
	virtual ~HoodieState() = default;

	virtual void update(Player& player, World& world, float& deltaTime);

	virtual void enter(Player& player);

	virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player, AttackHitbox& attackHitbox);

	virtual bool checkIfIsAttacking(Player& player, Player& enemy, const AttackHitbox& attackHitbox);

	virtual const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	virtual void attack(Player& player, Player& enemy) {}

	virtual void knockbackMove(Player& player, float& deltaTime) {}

private:
	std::string m_name{ "hoodie" };

	AttackHitbox m_attackHitbox{};
};
