#include "DeadState.h"

#include "Character.h"

DeadState::DeadState()
{
	m_stateName = "DeadState";
}

void DeadState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Dying"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Dying")), false);
}

CharacterState* DeadState::handleCondition(Character& character, const std::string& condition)
{
	return nullptr;
}

void DeadState::update(Character& character, float& deltaTime)
{
	character.m_velocity.y = 0.f;
}
