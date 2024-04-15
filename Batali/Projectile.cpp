#include "Projectile.h"

#include "IRenderComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"
#include "IAnimationComponent.h"

#include "ProjectileRenderComponent.h"
#include "ProjectileCollisionComponent.h"
#include "ProjectilePhysicsComponent.h"
#include "ProjectileAnimationComponent.h"

#include "ProjectileMovingState.h"

#include "BoxerUltimateState.h"

Projectile::Projectile(sf::Vector2f position, float direction, std::unique_ptr<IProjectileTypeState> projectileTypeState, const GameObject& launcher)
	: GameObject{}
	, m_projectileTypeState{ std::move(projectileTypeState) }
	, m_launcher{ launcher }
{
	m_renderComponent = std::make_unique<ProjectileRenderComponent>();
	m_collisionComponent = std::make_unique<ProjectileCollisionComponent>();
	m_physicsComponent = std::make_unique<ProjectilePhysicsComponent>();
	m_animationComponent = std::make_unique<ProjectileAnimationComponent>();

	m_facingRight = static_cast<int>(direction);

	m_projectileTypeState->enter(*this);

	m_projectileState = std::make_unique<ProjectileMovingState>();
	m_projectileState->enter(*this);

	m_animationComponent->initTextures(*this);

	m_sprite.setOrigin(sf::Vector2f{ 30 / 2.f, 30 / 2.f });
	
	// Initialize shape
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
}

void Projectile::updateAnimationThread()
{
	while (m_onAnimationThread)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		m_animationComponent->update(*this);
	}
}

void Projectile::setProjectileState(std::unique_ptr<IProjectileState> state)
{
	if (state != nullptr)
	{
		m_projectileState = std::move(state);

		m_projectileState->enter(*this);
	}
}

void Projectile::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	m_projectileState->update(*this);

	m_collisionComponent->update(*this, world);

	m_physicsComponent->update(*this, deltaTime);
}

void Projectile::render(sf::RenderWindow& window)
{
	m_renderComponent->render(*this, window);
}
