#include "Projectile.h"

#include "IRenderComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"
#include "IAnimationComponent.h"

Projectile::Projectile(IRenderComponent* renderComponent, ICollisionComponent* collisionComponent, IPhysicsComponent* physicsComponent, IAnimationComponent* animationComponent)
	: GameObject{}
	, m_renderComponent{ renderComponent }
	, m_collisionComponent{ collisionComponent }
	, m_physicsComponent{ physicsComponent }
	, m_animationComponent{ animationComponent }
{


	m_animationThread = std::thread{ &Projectile::updateAnimationThread, this };
}

Projectile::~Projectile()
{
	m_onAnimationThread = false;
	m_animationThread.join();

	if (m_renderComponent)
	{
		delete m_renderComponent;
		m_renderComponent = nullptr;
	}

	if (m_collisionComponent)
	{
		delete m_collisionComponent;
		m_collisionComponent = nullptr;
	}

	if (m_physicsComponent)
	{
		delete m_physicsComponent;
		m_physicsComponent = nullptr;
	}

	if (m_animationComponent)
	{
		delete m_animationComponent;
		m_animationComponent = nullptr;
	}
}

void Projectile::updateTexture()
{
	/*if (m_collided)
	{
		changeCurrentTexture(m_actorName + "Collision", "./assets/" + m_actorName + "/_Collision.png", false);
	}
	else
	{
		changeCurrentTexture(m_actorName + "Projectile", "./assets/" + m_actorName + "/_Projectile.png", true);
	}*/
}

void Projectile::updateAnimationThread()
{
	while (m_onAnimationThread)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		m_animationComponent->update(*this);
	}
}

void Projectile::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	/*if (!m_collided)
	{
		setVelocity(sf::Vector2f{ m_speed * m_facingRight, 0.f });
		move(deltaTime);
	}
	else
	{
		m_shape.setSize(sf::Vector2f{ 0.f, 0.f });
		m_shape.setPosition(-100.f, -100.f);

		if (m_currentTexture == m_actorName + "Collision" && m_animationEnd)
		{
			m_vanished = true;
		}
	}*/

	m_collisionComponent->update(*this, world, deltaTime);

	m_physicsComponent->update(*this, deltaTime);
}

void Projectile::render(sf::RenderWindow& window)
{
	m_renderComponent->render(*this, window);
}
