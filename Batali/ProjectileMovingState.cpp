#include "ProjectileMovingState.h"

#include "Projectile.h"
#include "IAnimationComponent.h"
#include "ProjectileCollidedState.h"

void ProjectileMovingState::update(Projectile& projectile)
{
	projectile.setVelocity(static_cast<float>(projectile.getSpeed() * projectile.getFacingRight()), 0.f);

	if (projectile.getCollided())
	{
		projectile.setProjectileState(new ProjectileCollidedState());
	}
}

void ProjectileMovingState::enter(Projectile& projectile)
{
	projectile.getAnimationComponent()->setNewAnimation(projectile, PROJECTILE_MOVING_ANIMATION, true);
}
