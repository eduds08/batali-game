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
class ILaunchProjectilesComponent;
class IAnimationComponent;
class IProjectileTypeState;
class IPlayerState;

class Player : public GameObject
{
public:
	Player(std::unique_ptr<IRenderComponent> renderComponent = nullptr, std::unique_ptr<ICollisionComponent> collisionComponent = nullptr, std::unique_ptr<IPhysicsComponent> physicsComponent = nullptr, std::unique_ptr<IAnimationComponent> animationComponent = nullptr, std::unique_ptr<ILaunchProjectilesComponent> launchProjectilesComponent = nullptr);
	virtual ~Player();

	void setChosenCharacter(std::unique_ptr<IChosenCharacterState> chosenCharacterState);

	void initKeyBindings();

	virtual void update(sf::RenderWindow& window, World& world, float& deltaTime);
	virtual void render(sf::RenderWindow& window);

	void handleCondition(const std::string& condition);

	void setPlayerState(std::unique_ptr<IPlayerState> state);

	void initAnimationThread();
	void updateAnimationThread();

	void takeDamage();
	void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }
	void setDamageToTake(int damageToTake) { m_damageToTake = damageToTake; }
	const int getHp() const { return m_hp; }
	const float getKnockbackVelocity() const { return m_knockbackVelocity; }

	std::unique_ptr<IAnimationComponent>& getAnimationComponent() { return m_animationComponent; }

	std::unique_ptr<IChosenCharacterState>& getChosenCharacter() { return m_chosenCharacterState; }

	sf::Keyboard::Scancode getKeyBinding(const std::string& keyBinding) { return m_keyBindings.at(keyBinding); }

	void launchProjectile(GameObject& gameObject, std::unique_ptr<IProjectileTypeState> projectileTypeState);
	const size_t getProjectilesSize() const;

	virtual const std::string& getName() const { return m_chosenCharacterState->getChosenCharacterName(); }

private:
	std::unique_ptr<IRenderComponent> m_renderComponent{ nullptr };
	std::unique_ptr<ICollisionComponent> m_collisionComponent{ nullptr };
	std::unique_ptr<IPhysicsComponent> m_physicsComponent{ nullptr };
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

	int m_hp{ 500 };
	float m_knockbackVelocity{ 0.f };

	int m_damageToTake{}; // weird, I know.
};
