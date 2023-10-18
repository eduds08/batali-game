#pragma once

#include "SwordEntity.h"
#include "Constants.h"

class Player : public SwordEntity
{
public:
	Player(sf::Vector2f firstPosition);
	virtual ~Player() = default;

	void update(float& deltaTime);

private:
	
};
