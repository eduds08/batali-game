#pragma once

#include "Character.h"

class FireKnight : public Character
{
public:
	FireKnight(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, std::shared_ptr<Character> player = nullptr);
	virtual ~FireKnight() = default;

	virtual void updateHitbox();
private:

};
