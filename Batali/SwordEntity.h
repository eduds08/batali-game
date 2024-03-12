#pragma once

#include "DamageEntity.h"

class SwordEntity : public DamageEntity
{
public:
	SwordEntity();
	virtual ~SwordEntity() = default;

	// Updates the state of m_isAttacking and also calls updateAttackHitbox()
	void updateAttack(bool attackCondition1, bool attackCondition2, bool ultimateCondition);

	void resetAttackHitbox() 
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}
	void resetUltimateHitbox() 
	{
		m_ultimateActivateHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_ultimateActivateHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}

	/* Setters */

	void setConditionAttack1(bool conditionAttack1) { m_conditionAttack1 = conditionAttack1; }
	void setConditionAttack2(bool conditionAttack2) { m_conditionAttack2 = conditionAttack2; }
	void setConditionUltimate(bool conditionUltimate) { m_conditionUltimate = conditionUltimate; }
	void setActivateUltimate(bool activateUltimate) { m_activateUltimate = activateUltimate; }

	/* Getters */

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }
	const int getDamage() const { return m_damage; }
	const std::string& getAttackMode() const { return m_attackMode; }
	const sf::RectangleShape& getUltimateActivateHitbox() const { return m_ultimateActivateHitbox; }

	// Defined inside each entity's class
	virtual void updateAttackHitbox() = 0;
	virtual void update(float& deltaTime) = 0;
	virtual const int getPlayerNumber() const = 0;

protected:
	sf::RectangleShape m_attackHitbox{sf::Vector2f{0.f, 0.f}};

	sf::RectangleShape m_ultimateActivateHitbox{sf::Vector2f{0.f, 0.f}};
	bool m_activateUltimate{ false };

	sf::Vector2f m_attackHitboxPosition{};

	float m_attackHitboxWidth{};
	float m_attackHitboxHeight{};

	std::string m_attackMode{"off"};

	bool m_conditionAttack1{ false };
	bool m_conditionAttack2{ false };
	bool m_conditionUltimate{ false };

	int m_damage{};
};
