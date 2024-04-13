#pragma once

#include "GameObject.h"
#include "InputHandler.h"

#include <unordered_map>
#include <thread>
#include <string>
#include <memory>

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
	Player(std::unique_ptr<IRenderComponent> renderComponent = nullptr, std::unique_ptr<ICollisionComponent> collisionComponent = nullptr, std::unique_ptr<IPhysicsComponent> physicsComponent = nullptr, std::unique_ptr<IAttackComponent> attackComponent = nullptr, std::unique_ptr<ILaunchProjectilesComponent> launchProjectilesComponent = nullptr, std::unique_ptr<IAnimationComponent> animationComponent = nullptr);
	virtual ~Player();

	void initChosenCharacter(std::unique_ptr<IChosenCharacterState> chosenCharacterState);

	virtual void update(sf::RenderWindow& window, World& world, float& deltaTime);
	virtual void render(sf::RenderWindow& window);

	virtual const std::string& getName() const { return m_chosenCharacterState->getChosenCharacterName(); }

	void handleHitted(int enemyDamage);
	void handleInput(sf::Keyboard::Scancode input);

	void setPlayerState(std::unique_ptr<IPlayerState> state);

	void updateAnimationThread();

	void initKeyBindings();

	std::unique_ptr<IAnimationComponent>& getAnimationComponent() { return m_animationComponent; }

	std::unique_ptr<IChosenCharacterState>& getChosenCharacter() { return m_chosenCharacterState; }

	sf::Keyboard::Scancode getKeyBinding(const std::string& keyBinding) { return m_keyBindings.at(keyBinding); }

	std::unique_ptr<IAttackComponent>& getAttackComponent() { return m_attackComponent; }
	std::unique_ptr<ILaunchProjectilesComponent>& getLaunchProjectilesComponent() { return m_launchProjectilesComponent; }

	void takeDamage(int enemyDamage);

	/* Damage attributes that will be stored here temporarily */
	int m_hp{ 1000 };

private:
	std::unique_ptr<IRenderComponent> m_renderComponent{ nullptr };
	std::unique_ptr<ICollisionComponent> m_collisionComponent{ nullptr };
	std::unique_ptr<IPhysicsComponent> m_physicsComponent{ nullptr };
	std::unique_ptr<IAttackComponent> m_attackComponent{ nullptr };
	std::unique_ptr<ILaunchProjectilesComponent> m_launchProjectilesComponent{ nullptr };
	std::unique_ptr<IAnimationComponent> m_animationComponent{ nullptr };

	std::unique_ptr<IChosenCharacterState> m_chosenCharacterState{ nullptr };

	std::unique_ptr<IPlayerState> m_playerState{ nullptr };

	std::thread m_animationThread{};
	bool m_onAnimationThread{ true };

	InputHandler m_inputHandler{};

	std::unordered_map<std::string, sf::Keyboard::Scancode> m_keyBindings{};

	static int s_playerNumberCounter;
	const int m_playerNumber;


	
};
