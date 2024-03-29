#pragma once

#include "ICollisionComponent.h"

#include "Constants.h"

using namespace constants;

class PlayerCollisionComponent : public ICollisionComponent
{
public:
	PlayerCollisionComponent();
	virtual ~PlayerCollisionComponent();

	virtual void update(Player& player, World& world, float& deltaTime);

	void updateCollisionWith(Player& player, const sf::Sprite& other);

	void handleCollision(Player& player);

	void updateLimits(Player& player);

	// Moves the actor after being hit. attackDirection -> direction of the attack (from left or right)
	void knockbackMove(Player& player, float& deltaTime, float attackDirection);

private:
	sf::Vector2f m_collisionDirection{};

	// Useful to make the actor stops when it is pushed against a wall after being knockbacked
	bool m_isCollidingHorizontally{ false };

	float m_knockbackVelocity{ KNOCKBACK_SPEED };

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	std::vector<float> m_shapeLimits{ 0.f, 0.f, 0.f, 0.f };
};
