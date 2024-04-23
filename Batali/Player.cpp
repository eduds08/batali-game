#include "Player.h"

#include "IRenderComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"
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

#include "World.h"

int Player::s_playerNumberCounter{ 1 };

Player::Player(std::unique_ptr<IRenderComponent> renderComponent, std::unique_ptr<ICollisionComponent> collisionComponent, std::unique_ptr<IPhysicsComponent> physicsComponent, std::unique_ptr<IAnimationComponent> animationComponent, std::unique_ptr<ILaunchProjectilesComponent> launchProjectilesComponent)
	: GameObject{}
	, m_renderComponent{ std::move(renderComponent) }
	, m_collisionComponent{ std::move(collisionComponent) }
	, m_physicsComponent{ std::move(physicsComponent) }
	, m_animationComponent{ std::move(animationComponent) }
	, m_launchProjectilesComponent{ std::move(launchProjectilesComponent) }
	, m_playerNumber{ s_playerNumberCounter }
{
	++s_playerNumberCounter;
}

Player::~Player()
{
	m_onAnimationThread = false;
	m_animationThread.join();

	m_keyBindings.clear();

	--s_playerNumberCounter;
}

void Player::setAttackComponent(std::unique_ptr<PlayerAttackComponent> attackComponent)
{
	m_playerAttackComponent = std::move(attackComponent);
	m_playerAttackComponent->enter(*this);
}

void Player::update(sf::RenderWindow& window, World& world, float& deltaTime)
{
	m_collisionComponent->update(*this, world);

	m_inputHandler.handleInput(*this);

	m_playerState->update(*this);

	m_playerAttackComponent->update(world, deltaTime);

	m_physicsComponent->update(*this, deltaTime);

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

void Player::handleCondition(const std::string& condition)
{
	std::unique_ptr<IPlayerState> playerState = m_playerState->handleCondition(*this, condition);

	if (playerState != nullptr)
	{
		m_playerState = std::move(playerState);

		m_playerState->enter(*this);
	}
}

void Player::setPlayerState(std::unique_ptr<IPlayerState> state)
{
	if (state != nullptr)
	{
		m_playerState = std::move(state);

		m_playerState->enter(*this);
	}
}

void Player::initAnimationThread()
{
	m_animationThread = std::thread{ &Player::updateAnimationThread, this };
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
	if (m_playerNumber == 1)
	{
		m_keyBindings.emplace("RUN_LEFT_BUTTON", sf::Keyboard::Scan::A);
		m_keyBindings.emplace("RUN_RIGHT_BUTTON", sf::Keyboard::Scan::D);
		m_keyBindings.emplace("JUMP_BUTTON", sf::Keyboard::Scan::W);
		m_keyBindings.emplace("ATTACK_1_BUTTON", sf::Keyboard::Scan::X);
		m_keyBindings.emplace("ATTACK_2_BUTTON", sf::Keyboard::Scan::C);
		m_keyBindings.emplace("ROLL_BUTTON", sf::Keyboard::Scan::V);
		m_keyBindings.emplace("ULTIMATE_BUTTON", sf::Keyboard::Scan::B);
	}
	else if (m_playerNumber == 2)
	{
		m_keyBindings.emplace("RUN_LEFT_BUTTON", sf::Keyboard::Scan::Left);
		m_keyBindings.emplace("RUN_RIGHT_BUTTON", sf::Keyboard::Scan::Right);
		m_keyBindings.emplace("JUMP_BUTTON", sf::Keyboard::Scan::Up);
		m_keyBindings.emplace("ATTACK_1_BUTTON", sf::Keyboard::Scan::I);
		m_keyBindings.emplace("ATTACK_2_BUTTON", sf::Keyboard::Scan::O);
		m_keyBindings.emplace("ROLL_BUTTON", sf::Keyboard::Scan::J);
		m_keyBindings.emplace("ULTIMATE_BUTTON", sf::Keyboard::Scan::K);
	}

	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("RUN_LEFT_BUTTON"), std::make_shared<RunLeftCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("RUN_RIGHT_BUTTON"), std::make_shared<RunRightCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("JUMP_BUTTON"), std::make_shared<JumpCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ATTACK_1_BUTTON"), std::make_shared<Attack1Command>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ATTACK_2_BUTTON"), std::make_shared<Attack2Command>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ROLL_BUTTON"), std::make_shared<RollCommand>());
	m_inputHandler.m_bindCommands.emplace(m_keyBindings.at("ULTIMATE_BUTTON"), std::make_shared<UltimateCommand>());
}

void Player::takeDamage()
{
	m_hp -= m_damageToTake;
}

void Player::launchProjectile(GameObject& gameObject, std::unique_ptr<IProjectileTypeState> projectileTypeState)
{
	m_launchProjectilesComponent->launchProjectile(gameObject, std::move(projectileTypeState));
}

const size_t Player::getProjectilesSize() const
{
	return m_launchProjectilesComponent->getProjectiles().size();
}
