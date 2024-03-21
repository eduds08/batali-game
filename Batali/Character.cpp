#include "Character.h"
#include "ColliderEntity.h"



Character::Character()
	: ColliderEntity{}
{
}

void Character::handleCondition(const std::string& condition)
{
	CharacterState* state = m_state->handleCondition(*this, condition);

	if (state != nullptr)
	{
		delete m_state;
		m_state = state;

		m_state->enter(*this);
	}
}

void Character::update(float& deltaTime)
{
	m_state->update(*this, deltaTime);
}
