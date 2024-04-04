#include "BoxerUltimateState.h"

#include "Projectile.h"

void BoxerUltimateState::setSpriteSize(Projectile& projectile)
{
	projectile.setSpriteSize(sf::Vector2i{ BOXER_ULTIMATE_PROJECTILE_SPRITE_HEIGHT, BOXER_ULTIMATE_PROJECTILE_SPRITE_WIDTH });
}

void BoxerUltimateState::setShapeSize(Projectile& projectile)
{
	projectile.getShape().setSize(sf::Vector2f{ BOXER_ULTIMATE_PROJECTILE_SHAPE_HEIGHT, BOXER_ULTIMATE_PROJECTILE_SHAPE_WIDTH });
}
