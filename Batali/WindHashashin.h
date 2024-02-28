#pragma once

#include "Character.h"

class WindHashashin : public Character
{
public:
	WindHashashin(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, std::shared_ptr<Character> player = nullptr);
	virtual ~WindHashashin() = default;

	virtual void updateHitbox();
private:

};
