#pragma once

#include "AttackEntity.h"
#include "Constants.h"

class Enemy : public AttackEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath, const sf::Vector2f& playerPosition, float spriteScale = 1.f);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	virtual void updateTexture();

private:
	
	sf::Clock clock{};
	float timeBetweenAttacks{};

	const sf::Vector2f& m_playerPosition;
};
