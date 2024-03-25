#pragma once

#include "Character.h"

class Hoodie : public Character
{
public:
	Hoodie(sf::Vector2f firstPosition, int playerNumber = 1);
	virtual ~Hoodie() = default;

	//void updateAttackHitbox();
	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox);
protected:

};
