#include "JumpingState.h"

#include "FallingState.h"

#include "Character.h"

void JumpingState::enter(Character& character)
{
	character.changeCurrentTexture(character.m_texturesActionName.at("Jumping"), character.m_texturesNamePath.at(character.m_texturesActionName.at("Jumping")), true);
	character.m_velocity.y = -1 * sqrt(2.f * GRAVITY * m_jumpHeight);
}

CharacterState* JumpingState::handleCondition(Character& character, const std::string& condition)
{
	if (condition == "ATTACK_1" || condition == "ATTACK_2")
	{

	}
	else if (character.m_velocity.y > 0.f)
	{
		return new FallingState{};
	}

    return nullptr;
}

void JumpingState::update(Character& character, float& deltaTime)
{
	character.m_velocity.y += GRAVITY * deltaTime;
}
