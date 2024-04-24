#pragma once

#include "PlayerAttackComponent.h"

class WindHashasinAttackComponent : public PlayerAttackComponent
{
public:
	WindHashasinAttackComponent() = default;
	virtual ~WindHashasinAttackComponent() = default;

	virtual void update(World& world, float& deltaTime);

private:
	virtual void updateAttack1(const int currentPlayerAnimationFrame);
	virtual void updateAttack2(const int currentPlayerAnimationFrame);
	virtual void updateAirAttack(const int currentPlayerAnimationFrame);
	virtual void updateUltimate(const int currentPlayerAnimationFrame);

	virtual void attack(Player& enemy);

	bool m_activeUltimate{ false };
};
