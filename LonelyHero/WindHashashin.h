#pragma once

#include "Character.h"

class WindHashashin : public Character
{
public:
	WindHashashin(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, Character* player = nullptr);
	virtual ~WindHashashin();

	virtual void updateHitbox();
private:

};
