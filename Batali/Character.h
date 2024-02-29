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

	const int getPlayerNumber() const { return m_playerNumber; }

	// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
	virtual void updateTexture();

	void setConditionRunLeft(bool conditionRunLeft, bool& resetClock) { m_conditionRunLeft = conditionRunLeft; if (conditionRunLeft) { resetClock = true; } }
	void setConditionRunRight(bool conditionRunRight, bool& resetClock) { m_conditionRunRight = conditionRunRight; if (conditionRunRight) { resetClock = true; }}
	void setConditionJump(bool conditionJump, bool& resetClock) { m_conditionJump = conditionJump; if (conditionJump) { resetClock = true; } }
	void setConditionAttack(bool conditionAttack, bool& resetClock) { m_conditionAttack = conditionAttack; if (conditionAttack) { resetClock = true; } }
	void setConditionRoll(bool conditionRoll, bool& resetClock) { m_conditionRoll = conditionRoll; if (conditionRoll) { resetClock = true; } }

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

	float m_hitboxWidthAttack1{};
	float m_hitboxWidthAttack2{};
	float m_hitboxWidthAirAttack{};

	int m_attack1Damage{};
	int m_attack2Damage{};
	int m_airAttackDamage{};
};
