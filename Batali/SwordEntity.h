#pragma once

#include "DamageEntity.h"

class SwordEntity : public DamageEntity
{
public:
	SwordEntity();
	virtual ~SwordEntity() = default;

	virtual void update(float& deltaTime);

	// Updates the state of m_isAttacking and also calls updateAttackHitbox()
	void updateAttack(bool attackCondition1, bool attackCondition2, bool ultimateCondition);

	void resetAttackHitbox() 
	{
		m_attackHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_attackHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}

	/* Getters */

	const sf::RectangleShape& getAttackHitbox() const { return m_attackHitbox; }
	const int getDamage() const { return m_damage; }
	const std::string& getAttackMode() const { return m_attackMode; }

	/* Pure Virtual Methods */

	virtual void updateAttackHitbox() = 0;

protected:
	sf::RectangleShape m_attackHitbox{sf::Vector2f{0.f, 0.f}};

	sf::Vector2f m_attackHitboxPosition{};

	float m_attackHitboxWidth{};
	float m_attackHitboxHeight{};

	std::string m_attackMode{"off"};

	bool m_conditionAttack1{ false };
	bool m_conditionAttack2{ false };
	bool m_conditionUltimate{ false };

	int m_damage{};
};
