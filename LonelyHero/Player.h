#pragma once

#include "SwordEntity.h"

class Player : public SwordEntity
{
public:
	Player(sf::Vector2f firstPosition, const std::string& chosenCharacter="FIRE_KNIGHT", int playerNumber=1);
	virtual ~Player() = default;

	void update(float& deltaTime);

	virtual void updateHitbox();

private:
	std::string m_chosenCharacter{"FIRE_KNIGHT"};
	int m_playerNumber{ 1 };
};
