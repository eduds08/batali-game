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

	void setConditionRunLeft(bool conditionRunLeft) { m_conditionRunLeft = conditionRunLeft; }
	void setConditionRunRight(bool conditionRunRight) { m_conditionRunRight = conditionRunRight;}
	void setConditionJump(bool conditionJump) { m_conditionJump = conditionJump; }
	void setConditionAttack(bool conditionAttack) { m_conditionAttack = conditionAttack; }
	void setConditionRoll(bool conditionRoll) { m_conditionRoll = conditionRoll; }

	void setConditionUltimate(bool conditionUltimate) { m_conditionUltimate = conditionUltimate; }

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

	bool m_conditionUltimate{ false };

	float m_hitboxWidthAttack1{};
	float m_hitboxWidthAttack2{};
	float m_hitboxWidthAirAttack{};
	float m_hitboxWidthUltimate{};

	int m_attack1Damage{};
	int m_attack2Damage{};
	int m_airAttackDamage{};
	int m_ultimateDamage{};
};
