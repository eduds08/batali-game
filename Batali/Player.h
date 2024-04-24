#pragma once

#include "GameObject.h"
#include "InputHandler.h"

#include <unordered_map>
#include <thread>
#include <string>
#include <memory>

#include "PlayerAttackComponent.h"

class IRenderComponent;
class ICollisionComponent;
class IPhysicsComponent;
class IAnimationComponent;
class IProjectileTypeState;
class IPlayerState;

class Player : public GameObject
{
public:
	Player(std::unique_ptr<IRenderComponent> renderComponent = nullptr, std::unique_ptr<ICollisionComponent> collisionComponent = nullptr, std::unique_ptr<IPhysicsComponent> physicsComponent = nullptr, std::unique_ptr<IAnimationComponent> animationComponent = nullptr);
	virtual ~Player();

	void setAttackComponent(std::unique_ptr<PlayerAttackComponent> attackComponent);

	void initKeyBindings();

	void update(sf::RenderWindow& window, World& world, float& deltaTime);
	virtual void render(sf::RenderWindow& window);

	void handleCondition(const std::string& condition);

	void setPlayerState(std::unique_ptr<IPlayerState> state);

	void initAnimationThread();
	void updateAnimationThread();

	void takeDamage();
	void setKnockbackVelocity(float knockbackVelocity) { m_knockbackVelocity = knockbackVelocity; }
	void setDamageToTake(int damageToTake) { m_damageToTake = damageToTake; }

	void setHp(int hp) { m_hp = hp; }
	const int getHp() const { return m_hp; }

	void setSpeed(float speed) { m_speed = speed; }
	const float getSpeed() const { return m_speed; }

	void setJumpHeight(float jumpHeight) { m_jumpHeight = jumpHeight; }
	const float getJumpHeight() const { return m_jumpHeight; }

	void setRollSpeed(float rollSpeed) { m_rollSpeed = rollSpeed; }
	const float getRollSpeed() const { return m_rollSpeed; }

	const float getKnockbackVelocity() const { return m_knockbackVelocity; }

	std::unique_ptr<IAnimationComponent>& getAnimationComponent() { return m_animationComponent; }

	std::unique_ptr<PlayerAttackComponent>& getAttackComponent() { return m_playerAttackComponent; }

	sf::Keyboard::Scancode getKeyBinding(const std::string& keyBinding) { return m_keyBindings.at(keyBinding); }

	void setName(const std::string& name) { m_name = name; }
	virtual const std::string& getName() const { return m_name; }

private:
	std::unique_ptr<IRenderComponent> m_renderComponent{ nullptr };
	std::unique_ptr<ICollisionComponent> m_collisionComponent{ nullptr };
	std::unique_ptr<IPhysicsComponent> m_physicsComponent{ nullptr };
	std::unique_ptr<IAnimationComponent> m_animationComponent{ nullptr };

	std::unique_ptr<PlayerAttackComponent> m_playerAttackComponent{ nullptr };

	std::unique_ptr<IPlayerState> m_playerState{ nullptr };

	std::thread m_animationThread{};
	bool m_onAnimationThread{ true };

	InputHandler m_inputHandler{};

	std::unordered_map<std::string, sf::Keyboard::Scancode> m_keyBindings{};

	std::string m_name{};

	static int s_playerNumberCounter;
	const int m_playerNumber;

	int m_hp{ 500 };
	float m_knockbackVelocity{ 0.f };
	float m_jumpHeight{};
	float m_rollSpeed{};

	float m_speed{};

	int m_damageToTake{}; // weird, I know.
};
