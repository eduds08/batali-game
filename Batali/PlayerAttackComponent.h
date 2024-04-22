#pragma once

#include "AttackHitbox.h"

class Player;
class World;

class PlayerAttackComponent
{
public:
	PlayerAttackComponent() = default;
	virtual ~PlayerAttackComponent() = default;

	virtual void update(Player& player, World& world, float& deltaTime);

	//virtual void enter(Player& player);

	//virtual const std::string& getChosenCharacterName() const { return m_name; }

	virtual void updateAttackHitbox(Player& player);

	virtual void updateAttack1(const int currentPlayerAnimationFrame) = 0;
	virtual void updateAttack2(const int currentPlayerAnimationFrame) = 0;
	virtual void updateAirAttack(const int currentPlayerAnimationFrame) = 0;
	virtual void updateUltimate(const int currentPlayerAnimationFrame) = 0;

	virtual bool isBeingAttackedBy(const AttackHitbox& enemyAttackHitbox, Player& thisPlayer);

	virtual const AttackHitbox& getAttackHitbox() const { return m_attackHitbox; }

	virtual void attack(Player& player, Player& enemy);

	virtual void knockbackMove(Player& player, float& deltaTime);

protected:
	AttackHitbox m_attackHitbox{};
};
