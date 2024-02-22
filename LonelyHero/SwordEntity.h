#pragma once

#include "DamageEntity.h"

class SwordEntity : public DamageEntity
{
public:
	SwordEntity(sf::Vector2f firstPosition);
	virtual ~SwordEntity() = default;

	// Updates the state of m_isAttacking and also calls updateHitbox()
	void updateAttack(bool attackCondition);

	virtual void updateHitbox() = 0;

	// Sets m_dead to true and "zeroes" some attributes
	virtual void die();

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }
	virtual bool getIsAttacking() { return m_isAttacking; }

	int getDamage() { return m_damage; }

protected:
	// Useful when entity has more than one attack animation. So it alters between one another
	std::string m_previousAttackingAnimation{};

	sf::RectangleShape m_attackHitbox{sf::Vector2f{0.f, 0.f}};

	float m_hitboxWidth{};
	float m_hitboxHeight{};

	bool m_isAttacking{ false };
	bool m_isAirAttacking{ false };

	// These attributes store the starting and ending frame of the attack sprite where the hitbox should spawn
	int m_attack1StartingFrame{};
	int m_attack1EndingFrame{};
	int m_attack2StartingFrame{};
	int m_attack2EndingFrame{};
	int m_airAttackingStartingFrame{};
	int m_airAttackingEndingFrame{};

	int m_damage{};
};
