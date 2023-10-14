#pragma once

#include "MovableEntity.h"

class DamageEntity : public MovableEntity
{
public:
	DamageEntity(int spriteWidth, int spriteHeight, float spriteScale, const std::string& textureName, const std::string& texturePath, int animationFramesAmount, const std::string& entityName, float shapeWidth, float shapeHeight, sf::Vector2f firstPosition);
	virtual ~DamageEntity() = default;

	void updateTakeDamage();

	void takeDamage(float& deltaTime);

	virtual bool getJustHitted() { return m_hitted; }

	bool isDead() { return m_dead; }

protected:
	sf::Clock m_cooldownDamageClock{};
	float m_cooldownDamage{};

	bool m_dead{ false };
	bool m_dying{ false };
	bool m_hitted{ false };

	int m_hp{ 1000 };
};
