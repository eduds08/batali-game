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
	}
}

void Character::update()
{
	m_state->update(*this);
}
