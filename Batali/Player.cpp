#include "Player.h"

Player::Player(IDrawingComponent* drawing, IAnimatingComponent* animating, ICollisionComponent* physics, IPhysicsComponent* collider)
	: m_drawingComponent{ drawing }
	, m_animatingComponent{ animating }
	, m_collisionComponent{ physics }
	, m_physicsComponent{ collider }
{
}

Player::~Player()
{
	if (m_drawingComponent)
	{
		delete m_drawingComponent;
		m_drawingComponent = nullptr;
	}
	if (m_animatingComponent)
	{
		delete m_animatingComponent;
		m_animatingComponent = nullptr;
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
}

void Player::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	m_collisionComponent->update(*this, world, deltaTime);

	//m_inputHandler.handleInput(*this);

	//m_state->update(*this, deltaTime);

	m_physicsComponent->update(*this, deltaTime);

	m_animatingComponent->update(*this);

	m_drawingComponent->render(*this, window);
}
