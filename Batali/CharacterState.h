#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class Character;

class CharacterState
{
public:
	virtual ~CharacterState() = default;

	virtual CharacterState* handleCondition(Character& character, const std::string& condition) = 0;

	virtual void update(Character& character) = 0;
};
