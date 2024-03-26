#pragma once

#include "Character.h"

class FireKnight : public Character
{
public:
	FireKnight(sf::Vector2f firstPosition);
	virtual ~FireKnight() = default;

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox);
};
