#pragma once

#include "IDrawingComponent.h"
#include "IAnimatingComponent.h"
#include "ICollisionComponent.h"
#include "IPhysicsComponent.h"

#include "PlayerAttackingComponent.h"

#include "World.h"
#include "InputHandler.h"

#include "PlayerFallingState.h"
#include "PlayerIdleState.h"

#include "Constants.h"

#include "FireKnightState.h"

#include <thread>
#include <chrono>

using namespace constants;

class Player
{
public:
	Player(IDrawingComponent* drawing = nullptr, IAnimatingComponent* animating = nullptr, ICollisionComponent* physics = nullptr, IPhysicsComponent* collider = nullptr);
	virtual ~Player();

	void update(sf::RenderWindow& window, World& world, float& deltaTime);
	void render(sf::RenderWindow& window);

	sf::Sprite& getSprite() { return m_sprite; }
	sf::RectangleShape& getShape() { return m_shape; }

	sf::Vector2f& getVelocity() { return m_velocity; }

	const std::string& getName() const { return m_chosenCharacterState->getChosenCharacterName(); }

	void handleInput(sf::Keyboard::Scancode input);

	void setPlayerState(IPlayerState* state);

	void updateAnimation();
	bool OnthreadTeste{ true };

	sf::Keyboard::Scancode JUMP_BUTTON = sf::Keyboard::Scancode::W;
	sf::Keyboard::Scancode RUN_LEFT_BUTTON = sf::Keyboard::Scancode::A;
	sf::Keyboard::Scancode RUN_RIGHT_BUTTON = sf::Keyboard::Scancode::D;
	sf::Keyboard::Scancode ATTACK_1_BUTTON = sf::Keyboard::Scancode::X;
	sf::Keyboard::Scancode ATTACK_2_BUTTON = sf::Keyboard::Scancode::C;
	sf::Keyboard::Scancode ROLL_BUTTON = sf::Keyboard::Scancode::V;
	sf::Keyboard::Scancode ULTIMATE_BUTTON = sf::Keyboard::Scancode::B;

	int m_facingRight{ 1 };

	IAnimatingComponent* getAnimatingComponent() { return m_animatingComponent; }

	IChosenCharacterState* getChosenCharacter() { return m_chosenCharacterState; }




	IAttackingComponent* m_attackingComponent{ new PlayerAttackingComponent() };




private:
	ICollisionComponent* m_collisionComponent{ nullptr };
	IPhysicsComponent* m_physicsComponent{ nullptr };
	IAnimatingComponent* m_animatingComponent{ nullptr };
	IDrawingComponent* m_drawingComponent{ nullptr };

	sf::Sprite m_sprite{};
	sf::RectangleShape m_shape{};

	sf::Vector2f m_velocity{};

	std::thread m_animatingThread;

	InputHandler m_inputHandler{};

	IPlayerState* m_playerState{ new PlayerFallingState() };

	IChosenCharacterState* m_chosenCharacterState{ new FireKnightState() };
};
