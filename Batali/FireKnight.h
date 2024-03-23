#pragma once

#include "Character.h"
#include  "AttackHitbox.h"

class FireKnight : public Character
{
public:
	FireKnight(sf::Vector2f firstPosition);
	virtual ~FireKnight() = default;

	//void updateAttackHitbox();

	virtual void updateAttackHitbox();

protected:
	AttackHitbox m_attackHitbox{};

};
