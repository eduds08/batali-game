#pragma once

#include "DamageEntity.h"

class SwordEntity : public DamageEntity
{
public:
	SwordEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~SwordEntity() = default;

	void updateHitbox();

	void updateAttack(bool condition);

	virtual void updateTexture();

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }

	virtual bool getIsAttacking() { return m_isAttacking; }

protected:
	// Useful when entity has more than one attack animation. So it alters between one another
	std::string m_previousAttackingAnimation{};

	sf::RectangleShape m_attackHitbox{};

	bool m_isAttacking{ false };

};

