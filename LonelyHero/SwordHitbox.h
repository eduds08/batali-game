#pragma once

#include "ColliderEntity.h"
#include "Constants.h"

class SwordHitbox : public ColliderEntity
{
public:
	SwordHitbox();
	~SwordHitbox();

	void setPosition(const sf::Vector2f& entityPosition) { m_shape.setPosition(entityPosition); }
};

