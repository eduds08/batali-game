#include "ProjectilePhysicsComponent.h"

#include "GameObject.h"

void ProjectilePhysicsComponent::update(GameObject& gameObject, float& deltaTime)
{
	move(gameObject, deltaTime);
}

void ProjectilePhysicsComponent::move(GameObject& gameObject, float& deltaTime)
{
	gameObject.getShape().move(gameObject.getVelocity() * deltaTime);
	gameObject.getSprite().setPosition(gameObject.getShape().getPosition());
}
