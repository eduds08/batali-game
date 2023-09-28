#pragma once

#include "ColliderEntity.h"
#include "Constants.h"

class SwordHitbox : public ColliderEntity
{
public:
	SwordHitbox(float shapeWidth = constants::swordHitboxWidth, float shapeHeight = constants::swordHitboxHeight, sf::Vector2f firstPosition = sf::Vector2f(0.f, 0.f));
	~SwordHitbox();

	void setPosition(const sf::Vector2f& entityPosition) { m_shape.setPosition(entityPosition); }

private:
};

