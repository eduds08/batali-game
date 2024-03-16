#pragma once

#include "ProjectileEntity.h"

class Boxer : public ProjectileEntity
{
public:
	Boxer(sf::Vector2f firstPosition);
	virtual ~Boxer() = default;

	void updateAttackHitbox();

	void updateCharacter(float& deltaTime);

private:
	
};
