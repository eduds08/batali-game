#pragma once

#include "GameObject.h"
#include "InputHandler.h"

#include <unordered_map>
#include <thread>
#include <string>

#include "IChosenCharacterState.h"

class IRenderComponent;
class ICollisionComponent;
class IPhysicsComponent;
class IAttackComponent;
class ILaunchProjectilesComponent;
class IAnimationComponent;

class IPlayerState;

class Player : public GameObject
{
public:
	Player(IRenderComponent* renderComponent = nullptr, ICollisionComponent* collisionComponent = nullptr, IPhysicsComponent* physicsComponent = nullptr, IAttackComponent* attackComponent = nullptr, ILaunchProjectilesComponent* launchProjectilesComponent = nullptr, IAnimationComponent* animationComponent = nullptr);
	virtual ~Player();

	void initChosenCharacter(IChosenCharacterState* chosenCharacterState);

	virtual void update(sf::RenderWindow& window, World& world, float& deltaTime);
	virtual void render(sf::RenderWindow& window);

	virtual const std::string& getName() const { return m_chosenCharacterState->getChosenCharacterName(); }

	void handleInput(sf::Keyboard::Scancode input);

	void setPlayerState(IPlayerState* state);

	void updateAnimationThread();

	void initKeyBindings();

	IAnimationComponent* getAnimationComponent() { return m_animationComponent; }

	IChosenCharacterState* getChosenCharacter() { return m_chosenCharacterState; }

	sf::Keyboard::Scancode getKeyBinding(const std::string& keyBinding) { return m_keyBindings.at(keyBinding); }

	IAttackComponent* getAttackComponent() { return m_attackComponent; }
	ILaunchProjectilesComponent* getLaunchProjectilesComponent() { return m_launchProjectilesComponent; }

private:
	IRenderComponent* m_renderComponent{ nullptr };
	ICollisionComponent* m_collisionComponent{ nullptr };
	IPhysicsComponent* m_physicsComponent{ nullptr };
	IAttackComponent* m_attackComponent{ nullptr };
	ILaunchProjectilesComponent* m_launchProjectilesComponent{ nullptr };
	IAnimationComponent* m_animationComponent{ nullptr };

	IPlayerState* m_playerState{ nullptr };

	IChosenCharacterState* m_chosenCharacterState{ nullptr };

	std::thread m_animationThread{};
	bool m_onAnimationThread{ true };

	InputHandler m_inputHandler{};

	std::unordered_map<std::string, sf::Keyboard::Scancode> m_keyBindings{};
};
