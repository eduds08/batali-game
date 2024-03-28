#include "Player.h"

Player::Player(IDrawingComponent* drawing, IAnimatingComponent* animating, IPhysicsComponent* physics, IMovingComponent* moving, IColliderComponent* collider)
	: m_drawingComponent{ drawing }
	, m_animatingComponent{ animating }
	, m_physicsComponent{ physics }
	, m_movingComponent{ moving }
	, m_colliderComponent{ collider }
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
	if (m_physicsComponent)
	{
		delete m_physicsComponent;
		m_physicsComponent = nullptr;
	}
	if (m_movingComponent)
	{
		delete m_movingComponent;
		m_movingComponent = nullptr;
	}
	if (m_colliderComponent)
	{
		delete m_colliderComponent;
		m_colliderComponent = nullptr;
	}
}

void Player::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	m_physicsComponent->update(*this, world, deltaTime);

	//m_inputHandler.handleInput(*this);

	//m_state->update(*this, deltaTime);

	// Moving Component:
	/*
	m_velocity.y += GRAVITY * deltaTime;
	this->move(deltaTime, -(m_spriteHeight - getShapeSize().y) / 2.f);
	m_velocity.x = 0.f;
	*/

	m_animatingComponent->update(*this);

	//m_movingComponent->update(*this, deltaTime);
	//m_colliderComponent->update(*this, deltaTime);

	m_drawingComponent->render(*this, window);
}
