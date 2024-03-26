#pragma once

#include "Character.h"

class WindHashashin : public Character
{
public:
	WindHashashin(sf::Vector2f firstPosition);
	virtual ~WindHashashin() = default;

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox);

	/* SETTERS */

	void setActivateUltimate(bool activateUltimate) { m_activateUltimate = activateUltimate; }
	const bool getActivateUltimate() const { return m_activateUltimate; }

protected:
	bool m_activateUltimate{ false };
};
