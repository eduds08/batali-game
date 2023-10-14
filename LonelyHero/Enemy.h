#pragma once

#include "SwordEntity.h"
#include "Constants.h"

class Enemy : public SwordEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

private:
	const sf::Vector2f& m_playerPosition;

	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};
};
