#pragma once

#include "CharacterState.h"

class AttackingState : public CharacterState
{
public:
	AttackingState(const std::string& attack);
	virtual ~AttackingState() = default;

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);

private:
	std::string m_attack{};

	sf::RectangleShape m_attackHitbox{ sf::Vector2f{0.f, 0.f} };
	sf::Vector2f m_attackHitboxPosition{};

	float m_attackHitboxWidth{};
	float m_attackHitboxHeight{};

	int m_damage{};
};
