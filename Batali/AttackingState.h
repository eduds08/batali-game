#pragma once

#include "CharacterState.h"

#include "AttackHitbox.h"

class AttackingState : public CharacterState
{
public:
	AttackingState(const std::string& attack);
	virtual ~AttackingState();

	virtual void enter(Character& character);

	virtual CharacterState* handleCondition(Character& character, const std::string& condition);

	virtual void update(Character& character, float& deltaTime);

	void handleAttack(Character& thisCharacter, Character& otherCharacter);

	AttackHitbox* m_attackHitbox{ nullptr };

private:
	std::string m_attack{};
};
