#include "PlayerPhysicsComponent.h"

#include "GameObject.h"

PlayerPhysicsComponent::PlayerPhysicsComponent()
{
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update(GameObject& gameObject, float& deltaTime)
{
	gameObject.setVelocity(gameObject.getVelocity().x, gameObject.getVelocity().y + GRAVITY * deltaTime);
	//gameObject.getVelocity().y += GRAVITY * deltaTime;

	gameObject.updateFlip();

	move(gameObject, deltaTime);

	gameObject.setVelocity(0.f, gameObject.getVelocity().y);
	//gameObject.getVelocity().x = 0.f;
}

void PlayerPhysicsComponent::move(GameObject& gameObject, float& deltaTime)
{
	gameObject.getShape().move(gameObject.getVelocity() * deltaTime);
	gameObject.getSprite().setPosition(gameObject.getShape().getPosition() + sf::Vector2f{ 0.f, -(gameObject.getSprite().getTextureRect().getSize().y - gameObject.getShape().getSize().y) / 2.f });
}
