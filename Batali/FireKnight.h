#pragma once

#include "SwordEntity.h"

class FireKnight : public SwordEntity
{
public:
	FireKnight(sf::Vector2f firstPosition);
	virtual ~FireKnight() = default;

	void updateAttackHitbox();

	void updateCharacter(float& deltaTime);

protected:

};
