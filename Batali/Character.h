#pragma once

#include "ColliderEntity.h"
#include "CharacterState.h"
#include "AttackHitbox.h"
#include "AttackingState.h"

class Character : public ColliderEntity
{
public:
	Character(int playerNumber = 1);
	virtual ~Character();

	void handleCondition(const std::string& condition);

	virtual void update(float& deltaTime);
	
	void setState(CharacterState* state);

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox) = 0;

	virtual void render(sf::RenderWindow& window, bool debugMode);

	const int* getHp() const { return &m_hp; }

	const int getPlayerNumber() const { return m_playerNumber; }

	const std::string& getStateName() const { return m_state->getStateName(); }

	friend class RollingState;
	friend class RunningState;
	friend class JumpingState;
	friend class FallingState;
	friend class IdleState;
	friend class AttackingState;
	friend class HittedState;
	friend class DeadState;

	template <class T>
	T* getCharacterState() const { return dynamic_cast<T*>(m_state); }

protected:
	CharacterState* m_state{ nullptr };

	int m_playerNumber{ 1 };
	int m_hp{ 1300 };
};
