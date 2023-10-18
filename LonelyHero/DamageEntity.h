#pragma once

#include "MovableEntity.h"

class DamageEntity : public MovableEntity
{
public:
	DamageEntity(sf::Vector2f firstPosition);
	virtual ~DamageEntity() = default;

	void updateCooldownDamage();
	void takeDamage(float& deltaTime, float direction);

	void knockbackMove(float& deltaTime, float direction);

	virtual bool getJustHitted() { return m_hitted; }
	bool isDead() { return m_dead; }

	void handleKnockbackVelocity();

protected:
	sf::Clock m_cooldownDamageClock{};
	float m_cooldownDamage{};

	bool m_dead{ false };
	bool m_dying{ false };
	bool m_hitted{ false };

	float m_knockbackVelocity{ constants::knockbackSpeed };

	int m_hp{ 1000 };
};
