#pragma once

#include "MovableEntity.h"

class AttackEntity : public MovableEntity
{
public:
	AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~AttackEntity() = default;

	void handleAttack(const std::string& entity);

	void updateHitbox(const std::string& entity);

	void updateTakeDamage(const std::string& entity);

	void takeDamage(float& deltaTime);

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }

	virtual bool getJustHitted() { return justHitted; }
	virtual bool getIsAttacking() { return m_isAttacking; }

	bool isDead() { return dead; }

	
	int hp{ 1000 };
	
	bool hitAltTemp{ false };

protected:

	// Useful when entity has more than one attack animation. So it alters between one another
	std::string m_previousAttackingAnimation{};

	sf::RectangleShape m_attackHitbox{};

	sf::Clock m_cooldownDamageClock{};
	float m_cooldownDamage{};

	bool dead{ false };
	bool justHitted{ false };
	bool m_isAttacking{ false };
};
