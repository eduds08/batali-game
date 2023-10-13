#pragma once

#include "AttackEntity.h"
#include "Constants.h"

class Enemy : public AttackEntity
{
public:
	Enemy(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition, const sf::Vector2f& playerPosition);
	virtual ~Enemy() = default;

	void update(float& deltaTime);

	void updateMovement(float& deltaTime);
	virtual void updateTexture();

	void updateAttack();

	void takeDamage(const sf::FloatRect& hitbox, float& deltaTime);

	int hp{ 1000 };

	bool justHitted{ false };
	bool hitAltTemp{ false };

	bool canJump{ false };

	void updateCanJump() { canJump = m_collisionDirection.y > 0.f; }

private:
	
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};

	sf::Clock m_cooldownDamageClock{};
	float m_cooldownDamage{};

	const sf::Vector2f& m_playerPosition;
};
