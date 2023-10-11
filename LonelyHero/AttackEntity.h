#pragma once

#include "MovableEntity.h"

class AttackEntity : public MovableEntity
{
public:
	AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~AttackEntity() = default;

	void handleAttack(const std::string& entity);

	void updateHitbox(const std::string& entity);

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }

	bool dead{ false };

protected:
	bool m_isAttacking{ false };

	// Useful when entity has more than one attack animation. So it alters between one another
	std::string m_previousAttackingAnimation{};

	sf::RectangleShape m_attackHitbox{};
};
