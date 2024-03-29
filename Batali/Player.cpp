#include "Player.h"

Player::Player(IDrawingComponent* drawing, IAnimatingComponent* animating, ICollisionComponent* physics, IPhysicsComponent* collider)
	: m_drawingComponent{ drawing }
	, m_animatingComponent{ animating }
	, m_collisionComponent{ physics }
	, m_physicsComponent{ collider }
{
	Tex->loadFromFile("./assets/fire_knight/_Idle.png");

	m_sprite.setTexture(*Tex);
	m_sprite.setTextureRect(sf::IntRect{ 0, 0, 288, 127 });

	m_sprite.setOrigin(sf::Vector2f{ 288 / 2.f, 127 / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ FIRE_KNIGHT_SHAPE_WIDTH, FIRE_KNIGHT_SHAPE_HEIGHT });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(LEFT_CHARACTER_FIRST_POSITION);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);
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

	//m_animatingComponent->update(*this);
}

void Player::render(sf::RenderWindow& window)
{
	m_drawingComponent->render(*this, window);
}
