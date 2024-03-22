#pragma once

#include "Character.h"

class Hoodie : public Character
{
public:
	Hoodie(sf::Vector2f firstPosition);
	virtual ~Hoodie() = default;

	//void updateAttackHitbox();
	virtual void updateAttackHitbox();
protected:

};
