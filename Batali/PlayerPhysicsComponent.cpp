#include "PlayerPhysicsComponent.h"

#include "Player.h"

PlayerPhysicsComponent::PlayerPhysicsComponent()
{
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update(Player& player, float& deltaTime)
{
	player.getVelocity().y += GRAVITY * deltaTime;

	move(player, deltaTime);

	player.getVelocity().x = 0.f;
}

void PlayerPhysicsComponent::move(Player& player, float& deltaTime)
{
	player.getShape().move(player.getVelocity() * deltaTime);
	player.getSprite().setPosition(player.getShape().getPosition() + sf::Vector2f{ 0.f, -(player.getSprite().getTextureRect().getSize().y - player.getShape().getSize().y) / 2.f });
}
