#pragma once

#include "SwordEntity.h"
#include "Constants.h"

class Enemy : public SwordEntity
{
public:
	Enemy(sf::Vector2f firstPosition, const sf::Vector2f& playerPosition);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

private:
	const sf::Vector2f& m_playerPosition;

	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};
};
