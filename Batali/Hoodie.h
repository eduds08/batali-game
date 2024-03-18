#pragma once

#include "SwordEntity.h"

class Hoodie : public SwordEntity
{
public:
	Hoodie(sf::Vector2f firstPosition);
	virtual ~Hoodie() = default;

	void updateAttackHitbox();

protected:

};
