#include "FallingState.h"

#include "IdleState.h"
#include "HittedState.h"
#include "Character.h"

void FallingState::enter(Character& character)
{
 	character.changeCurrentTexture(character.m_texturesActionName.at("Falling"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Falling")), true);
}

CharacterState* FallingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "IDLE")
	{
		return new IdleState{};
	}
	else if (condition == "HITTED")
	{
		return new HittedState{};
	}

	return nullptr;
}

void FallingState::update(Character& character, float& deltaTime)
{
	if (character.m_velocity.y == 0.f || character.m_collisionDirection.y < 0.f)
	{
		character.handleCondition("IDLE");
	}
}
