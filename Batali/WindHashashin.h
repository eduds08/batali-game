#pragma once

#include "Character.h"

class WindHashashin : public Character
{
public:
	WindHashashin(sf::Vector2f firstPosition);
	virtual ~WindHashashin() = default;

	//void updateAttackHitbox();

	void resetUltimateHitbox()
	{
		m_ultimateActivateHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_ultimateActivateHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox);

	virtual const sf::RectangleShape* getAttackHitbox() const
	{
		if (dynamic_cast<AttackingState*>(m_state) != nullptr)
		{
			if (dynamic_cast<AttackingState*>(m_state)->teste != nullptr && dynamic_cast<AttackingState*>(m_state)->teste->getShapeSize() != sf::Vector2f{0.f, 0.f})
			{
				return &(dynamic_cast<AttackingState*>(m_state)->teste->getShape());
			}
			else if (m_ultimateActivateHitbox.getSize() != sf::Vector2f{0.f, 0.f})
			{
				return &m_ultimateActivateHitbox;
			}
		}

		return nullptr;
	}

	/* SETTERS */

	void setActivateUltimate(bool activateUltimate) { m_activateUltimate = activateUltimate; }

	/* GETTERS */

	const sf::RectangleShape& getUltimateActivateHitbox() const { return m_ultimateActivateHitbox; }

protected:
	sf::RectangleShape m_ultimateActivateHitbox{ sf::Vector2f{0.f, 0.f} };
	bool m_activateUltimate{ false };
};
