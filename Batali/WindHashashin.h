#pragma once

#include "SwordEntity.h"

class WindHashashin : public SwordEntity
{
public:
	WindHashashin(sf::Vector2f firstPosition);
	virtual ~WindHashashin() = default;

	void updateAttackHitbox();

	void resetUltimateHitbox()
	{
		m_ultimateActivateHitbox.setSize(sf::Vector2f{ 0.f, 0.f });
		m_ultimateActivateHitbox.setPosition(sf::Vector2f{ -100.f, -100.f });
	}

	void updateCharacter(float& deltaTime);

	/* SETTERS */

	void setActivateUltimate(bool activateUltimate) { m_activateUltimate = activateUltimate; }

	/* GETTERS */

	const sf::RectangleShape& getUltimateActivateHitbox() const { return m_ultimateActivateHitbox; }

protected:
	sf::RectangleShape m_ultimateActivateHitbox{ sf::Vector2f{0.f, 0.f} };
	bool m_activateUltimate{ false };
};
