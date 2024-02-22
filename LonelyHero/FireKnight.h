#pragma once

#include "Character.h"

class FireKnight : public Character
{
public:
	FireKnight(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot = false, sf::Vector2f* playerPosition = nullptr);
	virtual ~FireKnight();

	void update(float& deltaTime);

	// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
	virtual void updateTexture();

	virtual void updateHitbox();
private:

};
