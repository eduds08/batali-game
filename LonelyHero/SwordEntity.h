#pragma once

#include "DamageEntity.h"

class SwordEntity : public DamageEntity
{
public:
	SwordEntity(sf::Vector2f firstPosition);
	virtual ~SwordEntity() = default;

	void updateAttack(bool condition);
	void updateHitbox();

	virtual void updateTexture();

	void die();

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }
	virtual bool getIsAttacking() { return m_isAttacking; }

protected:
	// Useful when entity has more than one attack animation. So it alters between one another
	std::string m_previousAttackingAnimation{};

	sf::RectangleShape m_attackHitbox{};

	bool m_isAttacking{ false };
};
