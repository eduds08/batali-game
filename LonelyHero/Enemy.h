#pragma once

#include "AnimatedEntity.h"
#include "ColliderEntity.h"
#include "Constants.h"

class Enemy : public AnimatedEntity, public ColliderEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, int animationFramesAmount, float shapeWidth, float shapeHeight, float spriteScale, sf::Vector2f firstPosition, const std::string& textureName, const std::string& texturePath, const sf::Vector2f& playerPosition);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	virtual void updateTexture();
private:
	
	sf::Clock clock{};
	float timeBetweenAttacks{};

	const sf::Vector2f& m_playerPosition;
};
