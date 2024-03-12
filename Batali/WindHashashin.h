#pragma once

#include "SwordEntity.h"

class WindHashashin : public SwordEntity
{
public:
	WindHashashin(sf::Vector2f firstPosition);
	virtual ~WindHashashin() = default;

	virtual void updateAttackHitbox();
private:

};
