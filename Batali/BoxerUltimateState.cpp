#include "BoxerUltimateState.h"

#include "Projectile.h"

void BoxerUltimateState::enter(Projectile& projectile)
{
	projectile.setSpriteSize(sf::Vector2i{ BOXER_ULTIMATE_PROJECTILE_SPRITE_HEIGHT, BOXER_ULTIMATE_PROJECTILE_SPRITE_WIDTH });
	projectile.getShape().setSize(sf::Vector2f{ BOXER_ULTIMATE_PROJECTILE_SHAPE_HEIGHT, BOXER_ULTIMATE_PROJECTILE_SHAPE_WIDTH });
	projectile.setSpeed(300);
}
