#include "SwordHitbox.h"

SwordHitbox::SwordHitbox()
	: ColliderEntity{ constants::swordHitboxWidth, constants::swordHitboxHeight, sf::Vector2f(0.f, 0.f) }
{
}

SwordHitbox::~SwordHitbox()
{
}
