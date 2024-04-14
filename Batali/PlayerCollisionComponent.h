#pragma once

#include "ICollisionComponent.h"

#include "Constants.h"

using namespace constants;

class PlayerCollisionComponent : public ICollisionComponent
{
public:
	PlayerCollisionComponent();
	virtual ~PlayerCollisionComponent();

	virtual void update(GameObject& gameObject, World& world, float& deltaTime);

	void updateCollisionWith(GameObject& gameObject, const sf::Sprite& other);

	void handleCollision(GameObject& gameObject);

	void updateLimits(GameObject& gameObject);

private:
	sf::Vector2f m_collisionDirection{};

	// Useful to make the actor stops when it is pushed against a wall after being knockbacked
	bool m_isCollidingHorizontally{ false };

	// 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
	std::vector<float> m_shapeLimits{ 0.f, 0.f, 0.f, 0.f };
};
