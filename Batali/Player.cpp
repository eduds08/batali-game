#include "Player.h"

#include "JumpCommand.h"
#include "RunRightCommand.h"
#include "RunLeftCommand.h"
#include "RollCommand.h"
#include "Attack1Command.h"
#include "Attack2Command.h"
#include "UltimateCommand.h"

int Player::idCounter{ 1 };

Player::Player(IDrawingComponent* drawing, IAnimatingComponent* animating, ICollisionComponent* physics, IPhysicsComponent* collider, IAttackingComponent* attackingComp, IProjectileComponent* proj)
	: m_drawingComponent{ drawing }
	, m_animatingComponent{ animating }
	, m_collisionComponent{ physics }
	, m_physicsComponent{ collider }
	, m_attackingComponent{ attackingComp }
	, m_projectileComponent{ proj }
	, m_playerNumber{ idCounter }
{
	m_inputHandler.m_bindCommands.emplace(ATTACK_1_BUTTON, new Attack1Command());
	m_inputHandler.m_bindCommands.emplace(JUMP_BUTTON, new JumpCommand());
	m_inputHandler.m_bindCommands.emplace(ROLL_BUTTON, new RollCommand());
	m_inputHandler.m_bindCommands.emplace(ATTACK_2_BUTTON, new Attack2Command());
	m_inputHandler.m_bindCommands.emplace(ULTIMATE_BUTTON, new UltimateCommand());
	m_inputHandler.m_bindCommands.emplace(RUN_LEFT_BUTTON, new RunLeftCommand());
	m_inputHandler.m_bindCommands.emplace(RUN_RIGHT_BUTTON, new RunRightCommand());

	m_animatingComponent->initTextures(*this);

	m_sprite.setOrigin(sf::Vector2f{ 288 / 2.f, 127 / 2.f });

	// Initialize shape
	m_shape.setSize(sf::Vector2f{ FIRE_KNIGHT_SHAPE_WIDTH, FIRE_KNIGHT_SHAPE_HEIGHT });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(LEFT_CHARACTER_FIRST_POSITION);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	m_animatingThread = std::thread{ &Player::updateAnimation, this };

	++idCounter;
}

Player::~Player()
{
	idCounter = 1;

	OnthreadTeste = false;
	m_animatingThread.join();

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
	if (m_attackingComponent)
	{
		delete m_attackingComponent;
		m_attackingComponent = nullptr;
	}
	if (m_projectileComponent)
	{
		delete m_projectileComponent;
		m_projectileComponent = nullptr;
	}
}

void Player::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	m_collisionComponent->update(*this, world, deltaTime);

	ICommand* command = m_inputHandler.handleInput();

	if (command)
	{
		command->execute(*this);
	}

	m_playerState->update(*this);

	m_physicsComponent->update(*this, deltaTime);

	m_attackingComponent->update(*this, world, deltaTime);

	if (m_projectileComponent != nullptr)
		m_projectileComponent->update(*this, world, deltaTime);

	//m_animatingComponent->update(*this);
}

void Player::render(sf::RenderWindow& window)
{
	m_drawingComponent->render(*this, window);
}

void Player::handleInput(sf::Keyboard::Scancode input)
{
	IPlayerState* playerState = m_playerState->handleInput(*this, input);

	if (playerState != nullptr)
	{
		delete m_playerState;
		m_playerState = playerState;

		m_playerState->enter(*this);
	}
}

void Player::setPlayerState(IPlayerState* state)
{
	if (state != nullptr)
	{
		delete m_playerState;
		m_playerState = state;

		m_playerState->enter(*this);
	}
}

void Player::updateAnimation()
{
	while (OnthreadTeste)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		m_animatingComponent->update(*this);
	}
}
