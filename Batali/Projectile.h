#pragma once

#include "GameObject.h"

#include <thread>

class IRenderComponent;
class ICollisionComponent;
class IPhysicsComponent;
class IAnimationComponent;

class Projectile : public GameObject
{
public:
	Projectile(IRenderComponent* renderComponent = nullptr, ICollisionComponent* collisionComponent = nullptr, IPhysicsComponent* physicsComponent = nullptr, IAnimationComponent* animationComponent = nullptr);
	virtual ~Projectile();

	virtual void update(sf::RenderWindow& window, World& world, float& deltaTime);
	virtual void render(sf::RenderWindow& window);

	void updateAnimationThread();

	/* SETTERS */

	void setCollided(bool collided) { m_collided = collided; }

	/* GETTERS */
	
	const bool getCollided() const { return m_collided; }
	const bool getVanished() const { return m_vanished; }
	const int getDamage() const { return m_damage; }

	virtual const std::string& getName() const { return "boxer_ultimate"; }

protected:
	IRenderComponent* m_renderComponent{ nullptr };
	ICollisionComponent* m_collisionComponent{ nullptr };
	IPhysicsComponent* m_physicsComponent{ nullptr };
	IAnimationComponent* m_animationComponent{ nullptr };

	std::thread m_animationThread{};
	bool m_onAnimationThread{ true };

	bool m_collided{ false };
	bool m_vanished{ false };

	int m_damage{};

};
