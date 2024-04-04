#include "ProjectileCollidedState.h"

#include "Projectile.h"
#include "IAnimationComponent.h"

void ProjectileCollidedState::update(Projectile& projectile)
{
	projectile.setVelocity(0.f, 0.f);

	if (projectile.getAnimationComponent()->getCurrentAnimation()->getAnimationEnd())
	{
		projectile.setVanished(true);
	}
}

void ProjectileCollidedState::enter(Projectile& projectile)
{
	projectile.getAnimationComponent()->setNewAnimation(projectile, PROJECTILE_COLLISION_ANIMATION, false);
}
