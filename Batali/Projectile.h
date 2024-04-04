#pragma once

#include "GameObject.h"

#include <thread>

class IRenderComponent;
class ICollisionComponent;
class IPhysicsComponent;
class IAnimationComponent;

class IProjectileState;

class Projectile : public GameObject
{
public:
	Projectile(sf::Vector2f position, float direction);
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

	virtual const std::string& getName() const { return nomeTeste; }

	std::string nomeTeste{"boxer_ultimate"};

	IAnimationComponent* getAnimationComponent() { return m_animationComponent; }

	void setProjectileState(IProjectileState* state);

	void setVanished(bool vanished) { m_vanished = vanished; }

	const int getSpeed() const { return m_speed; }

protected:
	IRenderComponent* m_renderComponent{ nullptr };
	ICollisionComponent* m_collisionComponent{ nullptr };
	IPhysicsComponent* m_physicsComponent{ nullptr };
	IAnimationComponent* m_animationComponent{ nullptr };

	IProjectileState* m_projectileState{ nullptr };

	std::thread m_animationThread{};
	bool m_onAnimationThread{ true };

	bool m_collided{ false };
	bool m_vanished{ false };

	int m_damage{};

	int m_speed{ 300 };

};
