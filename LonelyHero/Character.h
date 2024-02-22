#pragma once

#include "SwordEntity.h"
#include <random>

class Character : public SwordEntity
{
public:
	Character(sf::Vector2f firstPosition, int playerNumber=1, bool isBot = false, Character* player = nullptr);
	virtual ~Character() = default;

	void update(float& deltaTime);

	// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
	virtual void updateTexture();

protected:
	bool m_isBot{};

	// PLAYER ATTRIBUTES:
	int m_playerNumber{};

	// BOT ATTRIBUTES:
	const Character* m_player{};
	float m_distanceFromPlayer{};

	// Timer used to create a interval between the bot's attacks
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};
};
