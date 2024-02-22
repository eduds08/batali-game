#pragma once

#include "SwordEntity.h"
#include <random>

class Character : public SwordEntity
{
public:
	Character(sf::Vector2f firstPosition, int playerNumber = 1, bool isBot=false, sf::Vector2f* playerPosition=nullptr);
	virtual ~Character() = default;

protected:
	bool m_isBot{};

	// PLAYER ATTRIBUTES:
	int m_playerNumber{};

	// BOT ATTRIBUTES:
	const sf::Vector2f* m_playerPosition{};
	float m_distanceFromPlayer{};

	// Timer used to create a interval between the bot's attacks
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};
};
