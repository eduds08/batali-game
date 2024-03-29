#pragma once

#include "ColliderActor.h"
#include "CharacterState.h"
#include "AttackHitbox.h"
#include "AttackingState.h"

//#include "InputHandler.h"

class Character : public ColliderActor
{
public:
	Character();
	virtual ~Character();

	void handleCondition(const std::string& condition);

	virtual void update(float& deltaTime);
	
	void setState(CharacterState* state);

	virtual void updateAttackHitbox(AttackHitbox* m_attackHitbox) = 0;

	virtual void render(sf::RenderWindow& window, bool debugMode);

	const int* getHp() const { return &m_hp; }

	const std::string& getStateName() const { return m_state->getStateName(); }

	//const InputHandler& getInputHandler() const { return m_inputHandler; }

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

	static int m_playerNumber;
	int m_hp{ 1300 };

	//InputHandler m_inputHandler{};
};
