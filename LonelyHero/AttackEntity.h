#pragma once

#include "MovableEntity.h"

class AttackEntity : public MovableEntity
{
public:
	AttackEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~AttackEntity() = default;

	void updateAttack(const std::string& entity);

	void updateHitbox();

	const sf::RectangleShape& getHitbox() const { return m_hitbox; }

	bool justHitted{ false };
	bool dead{ false };

protected:
	bool m_isAttacking{ false };
	std::string m_previousAttackingAnimation{};

	sf::RectangleShape m_hitbox{};
};
