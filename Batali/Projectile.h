#pragma once

#include "GameObject.h"

#include <thread>

class IRenderComponent;
class ICollisionComponent;
class IPhysicsComponent;
class IAnimationComponent;

class IProjectileState;

class Player;

#include "IProjectileTypeState.h"

class Projectile : public GameObject
{
public:
	Projectile(sf::Vector2f position, float direction, std::unique_ptr<IProjectileTypeState> projectileTypeState, const GameObject& launcher);
	virtual ~Projectile();

	void update(World& world, float& deltaTime);
	virtual void render(sf::RenderWindow& window);

	void updateAnimationThread();

	/* SETTERS */

	void setCollided(bool collided) { m_collided = collided; }

	/* GETTERS */
	
	const bool getCollided() const { return m_collided; }
	const bool getVanished() const { return m_vanished; }
	const int getDamage() const { return m_damage; }

	virtual const std::string& getName() const { return m_projectileTypeState->getName(); }

	std::unique_ptr<IAnimationComponent>& getAnimationComponent() { return m_animationComponent; }

	void setProjectileState(std::unique_ptr<IProjectileState> state);

	void setVanished(bool vanished) { m_vanished = vanished; }

	void setSpeed(int speed) { m_speed = speed; }
	const int getSpeed() const { return m_speed; }

	const int getLauncherId() const { return m_launcher.getId(); }

protected:
	std::unique_ptr<IRenderComponent> m_renderComponent{ nullptr };
	std::unique_ptr<ICollisionComponent> m_collisionComponent{ nullptr };
	std::unique_ptr<IPhysicsComponent> m_physicsComponent{ nullptr };
	std::unique_ptr<IAnimationComponent> m_animationComponent{ nullptr };

	std::unique_ptr<IProjectileState> m_projectileState{ nullptr };
	std::unique_ptr<IProjectileTypeState> m_projectileTypeState{ nullptr };

	std::thread m_animationThread{};
	bool m_onAnimationThread{ true };

	bool m_collided{ false };
	bool m_vanished{ false };

	int m_damage{ 50 };

	int m_speed{};

	const GameObject& m_launcher;
};
