#pragma once

#include "SwordEntity.h"
#include <memory>
#include <random>

class Character : public SwordEntity
{
public:
	Character(sf::Vector2f firstPosition, int playerNumber=1, bool isBot = false, std::shared_ptr<Character> player = nullptr);
	virtual ~Character() = default;

	void update(float& deltaTime);

	int getPlayerNumber() { return m_playerNumber; }

	// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
	virtual void updateTexture();

	void setRunLeft(bool a) { m_conditionRunLeft = a; }
	void setRunRight(bool a) { m_conditionRunRight = a; }
	void setJump(bool a) { m_conditionJump = a; }
	void setConditionAttack(bool a) { m_conditionAttack = a; }
	void setConditionRoll(bool a) { m_conditionRoll = a; }

protected:
	bool m_isBot{};

	// PLAYER ATTRIBUTES:
	int m_playerNumber{};

	// BOT ATTRIBUTES:
	std::shared_ptr<Character> m_player{};
	float m_distanceFromPlayer{};

	// Timer used to create a interval between the bot's attacks
	sf::Clock m_timeBetweenAttacksClock{};
	float m_timeBetweenAttacks{};

	bool m_conditionRunLeft{ false };
	bool m_conditionRunRight{ false };
	bool m_conditionJump{ false };

	bool m_conditionAttack{ false };

	bool m_conditionRoll{ false };
};
