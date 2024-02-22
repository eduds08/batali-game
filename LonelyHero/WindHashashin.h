#pragma once

#include "Character.h"

class WindHashashin : public Character
{
public:
	WindHashashin(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, sf::Vector2f* playerPosition = nullptr);
	virtual ~WindHashashin();

	void update(float& deltaTime);

	// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
	virtual void updateTexture();

	virtual void updateHitbox();
private:

};
