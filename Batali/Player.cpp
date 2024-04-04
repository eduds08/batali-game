#include "Player.h"

#include "IRenderComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"
#include "IAttackComponent.h"
#include "ILaunchProjectilesComponent.h"
#include "IAnimationComponent.h"

#include "IPlayerState.h"

#include "RunRightCommand.h"
#include "RunLeftCommand.h"
#include "JumpCommand.h"
#include "Attack1Command.h"
#include "Attack2Command.h"
#include "RollCommand.h"
#include "UltimateCommand.h"

#include "PlayerFallingState.h"

#include "BoxerState.h"

Player::Player(std::unique_ptr<IRenderComponent> renderComponent, std::unique_ptr<ICollisionComponent> collisionComponent, std::unique_ptr<IPhysicsComponent> physicsComponent, std::unique_ptr<IAttackComponent> attackComponent, std::unique_ptr<ILaunchProjectilesComponent> launchProjectilesComponent, std::unique_ptr<IAnimationComponent> animationComponent)
	: GameObject{}
	, m_renderComponent{ std::move(renderComponent) }
	, m_collisionComponent{ std::move(collisionComponent) }
	, m_physicsComponent{ std::move(physicsComponent) }
	, m_attackComponent{ std::move(attackComponent) }
	, m_launchProjectilesComponent{ std::move(launchProjectilesComponent) }
	, m_animationComponent{ std::move(animationComponent) }
{
}

Player::~Player()
{
	m_onAnimationThread = false;
	m_animationThread.join();

	/*if (m_renderComponent)
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

	if (m_attackComponent)
	{
		delete m_attackComponent;
		m_attackComponent = nullptr;
	}

	if (m_launchProjectilesComponent)
	{
		delete m_launchProjectilesComponent;
		m_launchProjectilesComponent = nullptr;
	}

	if (m_animationComponent)
	{
		delete m_animationComponent;
		m_animationComponent = nullptr;
	}

	if (m_playerState)
	{
		delete m_playerState;
		m_playerState = nullptr;
	}

	if (m_chosenCharacterState)
	{
		delete m_chosenCharacterState;
		m_chosenCharacterState = nullptr;
	}*/
}

void Player::initChosenCharacter(std::unique_ptr<IChosenCharacterState> chosenCharacterState)
{
	m_chosenCharacterState = std::move(chosenCharacterState);
	m_chosenCharacterState->enter(*this);

	//m_playerState = new PlayerFallingState{};
	m_playerState = std::make_shared<PlayerFallingState>();
	m_playerState->enter(*this);

	initKeyBindings();

	m_animationComponent->initTextures(*this);

	m_shape.setPosition(LEFT_CHARACTER_FIRST_POSITION);

	// DEBUG
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(1.f);

	m_animationThread = std::thread{ &Player::updateAnimationThread, this };
}

void Player::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	m_collisionComponent->update(*this, world, deltaTime);

	std::shared_ptr<ICommand> command = m_inputHandler.handleInput();

	if (command)
	{
		command->execute(*this);
	}

	m_playerState->update(*this);

	m_physicsComponent->update(*this, deltaTime);

	m_attackComponent->update(*this, world, deltaTime);

	if (m_launchProjectilesComponent != nullptr)
		m_launchProjectilesComponent->update(*this, world, window, deltaTime);
}

void Player::render(sf::RenderWindow& window)
{
	m_renderComponent->render(*this, window);

	if (m_launchProjectilesComponent != nullptr)
	{
		for (const auto& proj : m_launchProjectilesComponent->getProjectiles())
		{
			proj->render(window);
		}
	}
}

void Player::handleInput(sf::Keyboard::Scancode input)
{
	std::shared_ptr<IPlayerState> playerState = m_playerState->handleInput(*this, input);

	if (playerState != nullptr)
	{
		//delete m_playerState;
		m_playerState = playerState;

		m_playerState->enter(*this);
	}
}

void Player::setPlayerState(std::shared_ptr<IPlayerState> state)
{
	if (state != nullptr)
	{
		//delete m_playerState;
		m_playerState = std::move(state);

		m_playerState->enter(*this);
	}
}

void Player::updateAnimationThread()
{
	while (m_onAnimationThread)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		m_animationComponent->update(*this);
	}
}

void Player::initKeyBindings()
{
	m_keyBindings.emplace("RUN_LEFT_BUTTON", sf::Keyboard::Scan::A);
	m_keyBindings.emplace("RUN_RIGHT_BUTTON", sf::Keyboard::Scan::D);
	m_keyBindings.emplace("JUMP_BUTTON", sf::Keyboard::Scan::W);
	m_keyBindings.emplace("ATTACK_1_BUTTON", sf::Keyboard::Scan::X);
	m_keyBindings.emplace("ATTACK_2_BUTTON", sf::Keyboard::Scan::C);
	m_keyBindings.emplace("ROLL_BUTTON", sf::Keyboard::Scan::V);
	m_keyBindings.emplace("ULTIMATE_BUTTON", sf::Keyboard::Scan::B);

	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("JUMP_BUTTON"), std::make_shared<JumpCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ATTACK_1_BUTTON"), std::make_shared<Attack1Command>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ATTACK_2_BUTTON"), std::make_shared<Attack2Command>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ROLL_BUTTON"), std::make_shared<RollCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ULTIMATE_BUTTON"), std::make_shared<UltimateCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("RUN_LEFT_BUTTON"), std::make_shared<RunLeftCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("RUN_RIGHT_BUTTON"), std::make_shared<RunRightCommand>());
}
