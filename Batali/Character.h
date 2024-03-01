#pragma once

#include "SwordEntity.h"
#include <memory>
#include <random>

class Character : public SwordEntity
{
public:
	Character(int playerNumber=1, bool isBot = false, std::shared_ptr<Character> player = nullptr);
	virtual ~Character() = default;

	void update(float& deltaTime);

	const int getPlayerNumber() const { return m_playerNumber; }

	// Changes the entity's texture according to its action (running, jumping, attacking, etc...)
	virtual void updateTexture();

protected:
	// PLAYER ATTRIBUTES:
	int m_playerNumber{};

	// BOT ATTRIBUTES:
	std::shared_ptr<Character> m_player{};
	float m_distanceFromPlayer{};
};
