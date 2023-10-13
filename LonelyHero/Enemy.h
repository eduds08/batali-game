#pragma once

#include "AttackEntity.h"
#include "Constants.h"

class Enemy : public AttackEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

	virtual void updateTexture();

	void updateAttack();

private:
	
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};

	const sf::Vector2f& m_playerPosition;
};
