#include "Projectile.h"

#include "IRenderComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"
#include "IAnimationComponent.h"

#include "ProjectileRenderComponent.h"
#include "ProjectileCollisionComponent.h"
#include "ProjectilePhysicsComponent.h"
#include "ProjectileAnimationComponent.h"

Projectile::Projectile(sf::Vector2f position, float direction)
	: GameObject{}
{
	m_renderComponent = new ProjectileRenderComponent{};
	m_collisionComponent = new ProjectileCollisionComponent{};
	m_physicsComponent = new ProjectilePhysicsComponent{};
	m_animationComponent = new ProjectileAnimationComponent{};

	m_animationComponent->initTextures(*this);

	

	m_sprite.setOrigin(sf::Vector2f{ 30 / 2.f, 30 / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ 30.f, 30.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	m_shape.setPosition(position);
	m_sprite.setPosition(position);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	m_animationComponent->setNewAnimation(*this, PROJECTILE_MOVING_ANIMATION, true);

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
	m_collisionComponent->update(*this, world, deltaTime);

	m_physicsComponent->update(*this, deltaTime);

	if (m_collided && m_animationComponent->getCurrentAnimation()->getAnimationEnd())
	{
		m_vanished = true;
	}

	if (m_collided)
	{
		m_animationComponent->setNewAnimation(*this, PROJECTILE_COLLISION_ANIMATION, false);
	}
	else
	{
		m_animationComponent->setNewAnimation(*this, PROJECTILE_MOVING_ANIMATION, true);
	}
}

void Projectile::render(sf::RenderWindow& window)
{
	m_renderComponent->render(*this, window);
}
