#pragma once

#include "Character.h"

class FireKnight : public Character
{
public:
	FireKnight(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, Character* player = nullptr);
	virtual ~FireKnight();

	virtual void updateHitbox();
private:

};
