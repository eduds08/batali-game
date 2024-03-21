#pragma once


#include "ColliderEntity.h"

class CharacterState;

class Character : public ColliderEntity
{
public:
	Character();
	virtual ~Character() {}

	void handleCondition(const std::string& condition);

	void update();

	CharacterState* m_state{ nullptr };

protected:

};
