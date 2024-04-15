#include "PlayerPhysicsComponent.h"

#include "GameObject.h"

void PlayerPhysicsComponent::update(GameObject& gameObject, float& deltaTime)
{
	// Add gravity
	gameObject.setVelocity(gameObject.getVelocity().x, gameObject.getVelocity().y + GRAVITY * deltaTime);

	// Flip sprite according to m_facingRight
	gameObject.updateFlip();

	// Moves shape and sprite
	move(gameObject, deltaTime);

	// Resets x-velocity to zero
	gameObject.setVelocity(0.f, gameObject.getVelocity().y);
}

void PlayerPhysicsComponent::move(GameObject& gameObject, float& deltaTime)
{
	gameObject.getShape().move(gameObject.getVelocity() * deltaTime);
	gameObject.getSprite().setPosition(gameObject.getShape().getPosition() + sf::Vector2f{ 0.f, -(gameObject.getSprite().getTextureRect().getSize().y - gameObject.getShape().getSize().y) / 2.f });
}
