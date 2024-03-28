#pragma once

#include "IPhysicsComponent.h"
#include "Player.h"

class PlayerPhysicsComponent : public IPhysicsComponent
{
public:
	PlayerPhysicsComponent();
	virtual ~PlayerPhysicsComponent();

	virtual void update(Player& player, World& world, float& deltaTime);

	void updateCollisionWith(Player& player, const sf::Sprite& other);

	void handleCollision(Player& player);

	void updateLimits(Player& player);

private:
	sf::Vector2f m_collisionDirection{};

	// Useful to make the actor stops when it is pushed against a wall after being knockbacked
	bool m_isCollidingHorizontally{ false };

	float m_knockbackVelocity{ KNOCKBACK_SPEED };

	sf::Vector2f m_velocity{};

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	std::vector<float> m_shapeLimits{ 0.f, 0.f, 0.f, 0.f };
};
