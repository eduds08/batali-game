#pragma once

#include "SwordEntity.h"

class Player : public SwordEntity
{
public:
	Player(sf::Vector2f firstPosition);
	virtual ~Player() = default;

	void update(float& deltaTime);

	virtual void updateHitbox();

private:
	
};
