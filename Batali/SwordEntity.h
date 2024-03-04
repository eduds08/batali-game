#pragma once

#include "DamageEntity.h"

class SwordEntity : public DamageEntity
{
public:
	SwordEntity();
	virtual ~SwordEntity() = default;

	// Updates the state of m_isAttacking and also calls updateHitbox()
	void updateAttack(bool attackCondition1, bool attackCondition2, bool ultimateCondition);

	virtual void updateHitbox() = 0;

	// Sets m_dead to true and "zeroes" some attributes
	virtual void die();

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }
	virtual const bool getIsAttacking() const { return m_isAttacking; }

	const int getDamage() const { return m_damage; }

	void setConditionAttack1(bool conditionAttack1) { m_conditionAttack1 = conditionAttack1; }
	void setConditionAttack2(bool conditionAttack2) { m_conditionAttack2 = conditionAttack2; }
	void setConditionUltimate(bool conditionUltimate) { m_conditionUltimate = conditionUltimate; }

	virtual const bool getOnUltimate() const { return m_onUltimate; }

	const sf::RectangleShape& getUltimateActivateHitbox() const { return m_ultimateActivateHitbox; }

	void setActivateUltimate(bool activateUltimate) { m_activateUltimate = activateUltimate; }

protected:
	// Useful when entity has more than one attack animation. So it alters between one another
	std::string m_previousAttackingAnimation{};
	bool m_isBot{};

	sf::RectangleShape m_attackHitbox{sf::Vector2f{0.f, 0.f}};

	sf::RectangleShape m_ultimateActivateHitbox{sf::Vector2f{0.f, 0.f}};
	bool m_activateUltimate{ false };

	float m_hitboxWidth{};
	float m_hitboxHeight{};

	bool m_isAttacking{ false };
	bool m_onAirAttack{ false };
	bool m_onUltimate{ false };
	bool m_onAttack1{ false };
	bool m_onAttack2{ false };

	float m_hitboxWidthAttack1{};
	float m_hitboxWidthAttack2{};
	float m_hitboxWidthAirAttack{};
	float m_hitboxWidthUltimate{};

	int m_attack1Damage{};
	int m_attack2Damage{};
	int m_airAttackDamage{};
	int m_ultimateDamage{};

	// Timer used to create a interval between the bot's attacks
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};

	bool m_conditionAttack1{ false };
	bool m_conditionAttack2{ false };
	bool m_conditionUltimate{ false };

	// These attributes store the starting and ending frame of the attack sprite where the hitbox should spawn
	int m_attack1StartingFrame{};
	int m_attack1EndingFrame{};
	int m_attack2StartingFrame{};
	int m_attack2EndingFrame{};
	int m_airAttackingStartingFrame{};
	int m_airAttackingEndingFrame{};
	int m_ultimateStartingFrame{};
	int m_ultimateEndingFrame{};

	int m_damage{};
};
