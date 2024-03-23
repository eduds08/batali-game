#pragma once

#include "CharacterState.h"

class RollingState : public CharacterState
{
public:
	RollingState() {}
	virtual ~RollingState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);

private:
	sf::Clock m_staminaRecoverClock{};
	int m_stamina{ 100 };
	float m_staminaRecoverTime{};

	float m_rollSpeed{ 220.f };
};
